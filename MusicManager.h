//
// Created by Guy Steinberg on 5/14/20.
//

#ifndef WET1_MUSICMANAGER_H
#define WET1_MUSICMANAGER_H

#include "library1.h"
#include "AVLTree.h"
#include "DoublyLinkedList.h"
#include "HelperDataStructs.h"

class MusicManager {
private:
    AVLTree<artistTreeData>* artistTree;
    DoublyLinkedList<recommendListData>* recommendList;


public:
    MusicManager();
    ~MusicManager();
    StatusType AddDataCenter(int artistID, int numOfSongs);
    StatusType RemoveData(int artistID);
    StatusType ArtistSongStreamed(int artistID, int songID);
    StatusType AmountOfStreams(int artistID, int songID, int* streams);
    StatusType GetRecommendations(int numOfSongs, int *artists, int* songs);

    void AddArtistTreeToRecomendations(AVLNode<sameNumTreeData>* minArtistNode, int* pos, int numOfSongs,int* artists, int *songs);
    void AddSongTreeToRecomendations(AVLNode<sameArtistTreeData>* minNode, int* pos, int numOfSongs, int artistID, int* artists, int* songs);
    void AddSongToRecomendations(int* pos, int artistID, int songID, int* artists, int* songs);

    void InOrderSameNumTree(AVLNode<sameNumTreeData>* root,int* pos, int numOfSongs, int* artists, int* songs);
    void InOrderSongIndexTree(AVLNode<sameArtistTreeData>* root, int* pos, int numOfSongs ,int artistID, int* artists, int* songs);

    StatusType CheckValidity(int artistID, int songID, bool returnFalseIfFound);

};
/**
 * Create empty data structure which includes:
 * ArtistTree (and AVL tree sorted by artistID)
 * RecommendList (DoublyLinkedList where each node represents number of streams)
 */
MusicManager::MusicManager() {

    //initialize empty artist tree using default constructor (root node is null)
    artistTree = new AVLTree<artistTreeData>();

    //initialize empty recomend list using default constructor (head, tail nodes are null)
    //each node in the list is like a "station" that holds all the songs with the same number of streams
    //with the head being the least (starts with 0 streams) and the tail being song with most number of streams (can be more than 1)
    recommendList = new DoublyLinkedList<recommendListData>();

    }

/**
*
* @param DS - pointer to data structure (artist tree)
* @param artistID - unique artist identifier
* @param numOfSongs - number of songs for this artist
* each song is identified by number (1...numOfSongs) and has 0 streams
* @return - StatusType based on result (ALLOCATION_ERROR, INVALID_INPUT, FAILURE, SUCCESS)
*/
StatusType MusicManager::AddDataCenter(int artistID, int numOfSongs) {

    //if artistID found then is is dupe and we return false(error)
    StatusType isValid = CheckValidity(artistID, 0, true);
    if( isValid != SUCCESS){
        return isValid;
    }

    //create new node in tree for artist and insert into correct position
    //array for artist's songs, initialize all have null pointers
    BasicNode<recommendListData> **artist_song_streams_arr = new BasicNode<recommendListData> *[numOfSongs];

    if(artistTree->Insert(artistTreeData(artistID, numOfSongs, artist_song_streams_arr))) {return ALLOCATION_ERROR;}

    //Song Index tree data for new artist node
    AVLTree<sameArtistTreeData>* songIndexTree = new AVLTree<sameArtistTreeData>();
    for(int i = 0; i < numOfSongs; i++){
        if(songIndexTree->Insert(sameArtistTreeData(i))) {return ALLOCATION_ERROR;}
    }

    sameNumTreeData newArtistNodeData = sameNumTreeData(artistID, songIndexTree);

    //check if the recommended list already has a "station" for songs with 0 streams
    BasicNode<recommendListData> *headStation = recommendList->getHead();

    if (headStation != NULL && headStation->getData().numberOfStreams == 0) {

        //Add the new artist node to the tree
        AVLTree<sameNumTreeData> *stationSameNumTree = headStation->getData().sameNumTree;
        if(stationSameNumTree->Insert(newArtistNodeData)) {return ALLOCATION_ERROR;}

    }
    else {
        AVLTree<sameNumTreeData>* sameNumTree = new AVLTree<sameNumTreeData>();
        if(sameNumTree->Insert(sameNumTreeData(artistID, songIndexTree))) {return ALLOCATION_ERROR;}

        //update start
        if(recommendList->InsertNodeHead(recommendListData(0, sameNumTree))) {return ALLOCATION_ERROR;}
    }

    headStation = recommendList->getHead();
    //update array so that all elements point to 0 "station" in the list
    for (int i = 0; i < numOfSongs; i++) {
        artist_song_streams_arr[i] = headStation;
    }

    return SUCCESS;
}

/**
 * delete associated artist with artist ID and all of his songs from DS
 * @param artistID - unique ID for the artist
 * @return appropiate StatusType based on Error
 */
StatusType MusicManager::RemoveData(int artistID) {

    //if artist found return true (not an error)
    StatusType isValid = CheckValidity(artistID,0, false);
    if (isValid != SUCCESS) {
        return isValid;
    }

    AVLNode<artistTreeData>* artist = artistTree->Find(artistTree->getRoot(), artistID);
    BasicNode<recommendListData>** artist_songs_streams_arr = artist->getData().songs;


    for(int i = 0; i<artist->getData().numOfSongs; i++) {
        AVLTree<sameNumTreeData>* currentStationTree = artist_songs_streams_arr[i]->getData().sameNumTree;

        AVLNode<sameNumTreeData>* root = currentStationTree->getRoot();

        //find artist Node in same num tree
        AVLNode<sameNumTreeData>* artistNode = currentStationTree->Find(root, artistID);

        //delete artist from current same num tree if exists (could be multiple songs with same streams so we deleted already)
        if(artistNode != NULL) {

            //delete song index avl tree recursively - happens in delete tree since it deletes all data of node (inc tree)
            currentStationTree->RemoveNode(currentStationTree->getRoot(),
                                           artistNode);
        }


    }
    //Delete artist songs stream array at the end, happens in node destructor
    //which is called in remove node
    artistTree->RemoveNode(artistTree->getRoot(), artist);

    return SUCCESS;
}

/**
 * An artist's song has been streamed -> update data structure
 * @param artistID - unique ID of the artist
 * @param songID - unique ID of the song streamed
 * @return appropiate error type or SUCCESS
 */
StatusType MusicManager::ArtistSongStreamed(int artistID, int songID) {

    StatusType isValid = CheckValidity(artistID, songID, false);
    if( isValid != SUCCESS){
        return isValid;
    }
    if (songID >= artistTree->Find(artistTree->getRoot(), artistID)->getData().numOfSongs) { return INVALID_INPUT; }


    AVLNode<artistTreeData>* artist = artistTree->Find(artistTree->getRoot(), artistID);
    //find the correct "station" in the list for the song which signifies the amount of streams the song has
    BasicNode<recommendListData> *currentSongStation = artist->getData().songs[songID];

    AVLTree<sameNumTreeData> *treeForCorrectStation = currentSongStation->getData().sameNumTree;
    AVLNode<sameNumTreeData> *root = treeForCorrectStation->getRoot();

    //get a pointer to the songID in the songIndexTree belonging to this artist in same num tree
    AVLTree<sameArtistTreeData> *songIndexForAppropriateStation = treeForCorrectStation->Find(
            root, artistID)->getData().artist_song_index;
    AVLNode<sameArtistTreeData> *songIndexRoot = songIndexForAppropriateStation->getRoot();
    AVLNode<sameArtistTreeData> *songNodeInIndex = songIndexForAppropriateStation->Find(
            songIndexRoot, songID);


    //find correct station to move this song to
    int numOfStreams = currentSongStation->getDataToCompare();
    BasicNode<recommendListData> *nextStation = currentSongStation->getNext();

    if (nextStation != NULL && nextStation->getData().numberOfStreams == numOfStreams + 1) {
        //get node for current artist in same num tree
        AVLTree<sameNumTreeData>* sameNumTree = nextStation->getData().sameNumTree;
        AVLNode<sameNumTreeData> *treeRoot = sameNumTree->getRoot();
        AVLNode<sameNumTreeData> *artistNode = sameNumTree->Find(
                treeRoot, artistID);

        if (artistNode == NULL) {
            //artist not found in station tree - create new node and add to the tree
            AVLTree<sameArtistTreeData> *songIndexTree = new AVLTree<sameArtistTreeData>();
            songIndexTree->Insert(sameArtistTreeData(songID));

            sameNumTreeData newArtistData = sameNumTreeData(artistID, songIndexTree);
            if(nextStation->getData().sameNumTree->Insert(newArtistData)) {return  ALLOCATION_ERROR;}


        } else {

            //artist was found in the current same num tree - insert song
            if(artistNode->getData().artist_song_index->Insert(sameArtistTreeData(songID))) {return ALLOCATION_ERROR;}
        }

        //update song array containing pointers to station
        artist->getData().songs[songID] = nextStation;

    } else {

        //insert new station in between these 2 stations and add the song to appropriate tree
        AVLTree<sameArtistTreeData>* songIndexTree = new AVLTree<sameArtistTreeData>();
        if(songIndexTree->Insert(sameArtistTreeData(songID))) {return ALLOCATION_ERROR;}


        AVLTree<sameNumTreeData>* sameNumTree = new AVLTree<sameNumTreeData>();
        if(sameNumTree->Insert(sameNumTreeData(artistID, songIndexTree))) {return ALLOCATION_ERROR;}

        if(recommendList->InsertNodeBetween(currentSongStation, nextStation, recommendListData(numOfStreams + 1, sameNumTree))) {return ALLOCATION_ERROR;}

        //update song array containing pointers to station
        artist->getData().songs[songID] = currentSongStation->getNext();

    }

    //now we can delete old song node from its previous song Index tree
    songIndexForAppropriateStation->RemoveNode(songIndexForAppropriateStation->getRoot(), songNodeInIndex);

    if (songIndexForAppropriateStation->getRoot() == NULL){
        //removing artistID from station
        treeForCorrectStation->RemoveNode(treeForCorrectStation->getRoot(),
                treeForCorrectStation->Find(treeForCorrectStation->getRoot(), artistID));

       if(treeForCorrectStation->getRoot() ==NULL){
           //removing station
           recommendList->RemoveNode(currentSongStation);
       }
    }

    return SUCCESS;
}

/**
 * get number of streams for songID by artistID and put value into streams
 * @param artistID - unique ID for the artist
 * @param songID - unique ID for the song
 * @param streams - number of streams for the song
 * @return appropiate enum type if encountered an error
 */
StatusType MusicManager::AmountOfStreams(int artistID, int songID, int *streams) {

    StatusType isValid = CheckValidity(artistID, songID, false);
    if(isValid != SUCCESS) {
        return isValid;
    }
    if (songID >=artistTree->Find(artistTree->getRoot(), artistID)->getData().numOfSongs) { return INVALID_INPUT; }

    AVLNode<artistTreeData>* artist = artistTree->Find(artistTree->getRoot(), artistID);
    //find the correct "station" in the list for the song which signifies the amonut of streams the song has
    BasicNode<recommendListData> *currentSongStation = artist->getData().songs[songID];
    *streams = currentSongStation->getData().numberOfStreams;

    return SUCCESS;
}

/**
 * Get numOfSongs most played songs in descending order
 * @param numOfSongs
 * @param artists
 * @param songs
 * @return appropiate error if encountered during function execution
 */
StatusType  MusicManager::GetRecommendations(int numOfSongs, int *artists, int *songs) {
    //check validity
    if(numOfSongs <= 0) return INVALID_INPUT;

    //keeps track of how many song recommendations we have added so far (also position in array to add them to since we start at 0)
    int songsRecommended = 0;
    int* pos = &songsRecommended;


    //get the last station in the doublyLinkedList
    BasicNode<recommendListData>* tailStation = recommendList->getTail();

    while(*pos < numOfSongs && tailStation != NULL) {

        //add the artists tree of this station
        AVLTree<sameNumTreeData>* mostStreamedArtistTree = tailStation->getData().sameNumTree;
        AddArtistTreeToRecomendations(mostStreamedArtistTree->getMinNode(), pos, numOfSongs, artists, songs);

        //advance to previous station (next highest in streams)
        tailStation = tailStation->getPrev();

    }

    if(*pos < numOfSongs && tailStation == NULL) {
        //less songs in Data Structure than numOfSongs (not enough songs to return)
        return FAILURE;
    }
    return SUCCESS;
}

/**
 * ends execution by releasing all stored memory of Data Structure
 */

MusicManager::~MusicManager() {
    //Delete Main Tree and all arrays of artists inside of it
    delete(this->artistTree);

    //Delete RecommendList and all trees and sub trees inside
    delete(this->recommendList);
}

//HELPER FUNCTIONS


void MusicManager::InOrderSameNumTree(AVLNode<sameNumTreeData>* root,int* pos, int numOfSongs, int* artists, int* songs){

    if (root != NULL && *pos < numOfSongs) {
        InOrderSameNumTree(root->getLeft(),pos, numOfSongs, artists, songs);

        //Add the entire song tree (or as many songs) of this artist if possible (since he is next in line)
        AddSongTreeToRecomendations(root->getData().artist_song_index->getMinNode(), pos, numOfSongs, root->getData().artistID, artists, songs);

        InOrderSameNumTree(root->getRight(),pos, numOfSongs, artists, songs);
    }

}
void MusicManager::InOrderSongIndexTree(AVLNode<sameArtistTreeData>* root, int* pos, int numOfSongs,int artistID, int* artists, int* songs){

    if(root != NULL && *pos < numOfSongs) {
        InOrderSongIndexTree(root->getLeft(), pos,numOfSongs, artistID, artists, songs);

        //add song to reccomendation arrays
        AddSongToRecomendations(pos, artistID, root->getData().songIndex, artists, songs);

        InOrderSongIndexTree(root->getRight(), pos,numOfSongs, artistID, artists, songs);
    }

}
void MusicManager::AddSongToRecomendations(int* pos, int artistID, int songID, int* artists, int* songs){

    artists[*pos] = artistID;
    songs[*pos] = songID;
    *pos = *pos + 1;


}
void MusicManager::AddSongTreeToRecomendations(AVLNode<sameArtistTreeData>* minNode, int* pos, int numOfSongs, int artistID, int* artists, int* songs){

    //initially min value song but gets updated to be node we add to recommendation each iteration
    AVLNode<sameArtistTreeData> *songParent = minNode;

    //either we have enough songs or we reached end of song tree
    while (songParent != NULL && *pos < numOfSongs) {
        //Add min value song to recommendation arrays

        int songID = songParent->getData().songIndex;

        AddSongToRecomendations(pos, artistID, songID, artists, songs);

        //scan right sub tree (and add all songs with it)
        InOrderSongIndexTree(songParent->getRight(), pos, numOfSongs,
                             artistID, artists, songs);
        songParent = songParent->getParent();
    }

}

void MusicManager::AddArtistTreeToRecomendations(AVLNode<sameNumTreeData>* minArtistNode, int* pos, int numOfSongs,int* artists, int *songs){

    AVLNode<sameNumTreeData>* artistParent = minArtistNode;
    while(artistParent != NULL && *pos < numOfSongs) {
        int artistID = artistParent->getData().artistID;
        //Add this artist's songs to recommendations based on ascending value (per exercise rules)
        AddSongTreeToRecomendations(artistParent->getData().artist_song_index->getMinNode(), pos, numOfSongs, artistID, artists, songs);

        //check right sub tree of artists and add as many songs from there
        InOrderSameNumTree(artistParent->getRight(), pos, numOfSongs, artists, songs);

        //go up in tree (update parent node)
        artistParent = artistParent->getParent();
    }

}

StatusType MusicManager::CheckValidity(int artistID, int songID, bool returnFalseIfFound){

    if (songID < 0 || artistID <= 0) return INVALID_INPUT;

    AVLNode<artistTreeData> *found_artist = artistTree->Find(artistTree->getRoot(), artistID);
    if(returnFalseIfFound) {
        if (found_artist != NULL) { return FAILURE; }
    } else {
        if (found_artist == NULL) { return FAILURE; }
    }

    return SUCCESS;
}



#endif //WET1_MUSICMANAGER_H
