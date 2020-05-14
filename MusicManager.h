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
    StatusType AddDataCenter(int artistID, int numOfSongs);
    StatusType RemoveData(int artistID);
    StatusType ArtistSongStreamed(int artistID, int songID);
    StatusType AmountOfStreams(int artistID, int songID, int* streams);
    StatusType GetRecommendations(int numOfSongs, int *artists, int* songs);
    void EndProgram();
};
/**
 * Create empty data structure which includes:
 * ArtistTree (and AVL tree sorted by artistID)
 * RecommendList (DoublyLinkedList where each node represents number of streams)
 */
MusicManager::MusicManager() {
    //TODO add case of failure - return NULL?
    //initialize empty artist tree using default constructor (root node is NULL)
    artistTree = new AVLTree<artistTreeData>();

    //initialize empty recomend list using default constructor (head, tail nodes are NULL)
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
    //check invalid input
    if (artistID <= 0 || numOfSongs <= 0) {
        return INVALID_INPUT;
    }
    //check existing artistID
    AVLNode<artistTreeData> *root = artistTree->getRoot();
    if (artistTree->Find(root, artistID)) {
        return FAILURE;
    }

    //create new node in tree for artist and insert into correct position
    //array for artist's songs, initialize all have NULL pointers
    BasicNode<recommendListData> **artist_song_streams_arr = new BasicNode<recommendListData> *[numOfSongs];
    artistTreeData newArtistData = artistTreeData(artistID, numOfSongs, artist_song_streams_arr);

    if(artistTree->Insert(newArtistData)) {return ALLOCATION_ERROR;}

    //Song Index tree data for new artist node
    //TODO create songIndexTree (AVL tree) containing nodes from 1...numOfSongs

    sameNumTreeData newArtistNodeData = sameNumTreeData(artistID, songIndexTree);

    //check if the recommended list already has a "station" for songs with 0 streams
    BasicNode<recommendListData> *headStation = recommendList->getHead();
    if (headStation->getData().numberOfStreams == 0) {

        //Add the new artist node to the tree
        AVLTree<sameNumTreeData> *stationSameNumTree = headStation->getData().sameNumTree;
        if(stationSameNumTree->Insert(newArtistNodeData)) {return ALLOCATION_ERROR;}

    } else {

        sameNumTreeData newArtistData = sameNumTreeData(artistID, songIndexTree);
        AVLTree<sameNumTreeData>* sameNumTree = new AVLTree<sameNumTreeData>();
        if(sameNumTree->Insert(newArtistData)) {return ALLOCATION_ERROR;}

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
    if(artistID <= 0) return INVALID_INPUT;

    //check existing artistID
    AVLNode<artistTreeData> *root = artistTree->getRoot();
    AVLNode<artistTreeData> *artist = artistTree->Find(root, artistID);
    if(artist == NULL) return FAILURE; //didn't find artist

    BasicNode<recommendListData>** artist_songs_streams_arr = artist->getData().songs;

    for(int i = 0; i<artist->getData().numOfSongs; i++) {
        AVLTree<sameNumTreeData>* currentStationTree = artist_songs_streams_arr[i]->getData().sameNumTree;
        AVLNode<sameNumTreeData>* root = currentStationTree->getRoot();

        //find artist Node in same num tree
        AVLNode<sameNumTreeData>* artistNode = currentStationTree->Find(root, artistID);
        //delete song index avl tree recursively
        artistNode->getData().artist_song_index->DeleteTree(artistNode->getData().artist_song_index->getRoot());

        //delete artist from current same num tree
        currentStationTree->RemoveNode(artistNode);

    }

    //Delete artist songs stream array at the end
    delete [] artist_songs_streams_arr;

    return SUCCESS;
}

/**
 * An artist's song has been streamed -> update data structure
 * @param artistID - unique ID of the artist
 * @param songID - unique ID of the song streamed
 * @return appropiate error type or SUCCESS
 */
StatusType MusicManager::ArtistSongStreamed(int artistID, int songID) {
    //Checking input validity TODO - export to validity function
    if (songID < 0 || artistID <= 0) return INVALID_INPUT;
    AVLNode<artistTreeData> *found_artist = artistTree->Find(
            artistTree->getRoot(), artistID);
    if (found_artist == NULL) { return FAILURE; }
    else {
        if (songID >=
            found_artist->getData().numOfSongs) { return INVALID_INPUT; }
    }

    //find the correct "station" in the list for the song which signifies the amonut of streams the song has
    BasicNode<recommendListData> *currentSongStation = found_artist->getData().songs[songID];
    AVLTree<sameNumTreeData> *treeForCorrectStation = currentSongStation->getData().sameNumTree;
    AVLNode<sameNumTreeData> *root = treeForCorrectStation->getRoot();

    //get a pointer to the songID in the songIndexTree belonging to this artist in same num tree
    AVLTree<sameArtistTreeData> *songIndexForAppropiateStation = treeForCorrectStation->Find(
            root, artistID)->getData().artist_song_index;
    AVLNode<sameArtistTreeData> *songIndexRoot = songIndexForAppropiateStation->getRoot();
    AVLNode<sameArtistTreeData> *songNodeInIndex = songIndexForAppropiateStation->Find(
            songIndexRoot, songID);


    //find correct station to move this song to
    int numOfStreams = currentSongStation->getDataToCompare();
    BasicNode<recommendListData> *nextStation = currentSongStation->getNext();

    if (nextStation->getData().numberOfStreams == numOfStreams + 1) {
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
            //artist was found in the current same num tree - insert new song
            if(artistNode->getData().artist_song_index->Insert(sameArtistTreeData(songID))) {return ALLOCATION_ERROR;}
        }

        //update song array containing pointers to station
        found_artist->getData().songs[songID] = nextStation;

    } else {
        //insert new station in between these 2 stations and add the song to appropiate tree
        AVLTree<sameArtistTreeData>* songIndexTree = new AVLTree<sameArtistTreeData>();
        if(songIndexTree->Insert(sameArtistTreeData(songID))) {return ALLOCATION_ERROR;}

        sameNumTreeData newArtistData = sameNumTreeData(artistID, songIndexTree);
        AVLTree<sameNumTreeData>* sameNumTree = new AVLTree<sameNumTreeData>();
        if(sameNumTree->Insert(newArtistData)) {return ALLOCATION_ERROR;}

        if(recommendList->InsertNodeAfter(currentSongStation, recommendListData(numOfStreams + 1, sameNumTree))) {return ALLOCATION_ERROR;}

        //update song array containing pointers to station
        found_artist->getData().songs[songID] = currentSongStation->getNext();
    }
    //now we can delete old song node from its previous song Index tree
    songIndexForAppropiateStation->RemoveNode(songNodeInIndex);

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
    //Checking input validity TODO - export to validity function
    if (songID < 0 || artistID <= 0) return INVALID_INPUT;
    AVLNode<artistTreeData> *found_artist = artistTree->Find(
            artistTree->getRoot(), artistID);
    if (found_artist == NULL) { return FAILURE; }
    else {
        if (songID >=
            found_artist->getData().numOfSongs) { return INVALID_INPUT; }
    }
    //find the correct "station" in the list for the song which signifies the amonut of streams the song has
    BasicNode<recommendListData> *currentSongStation = found_artist->getData().songs[songID];
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
    //get the last station in the doublyLinkedList
    BasicNode<recommendListData>* tailStation = recommendList->getTail();

    //find the minimum song belonging to the minimum artist in the tree (based on order in both AVL trees)
    AVLTree<sameNumTreeData>* mostStreamedArtistTree = tailStation->getData().sameNumTree;
    AVLNode<sameNumTreeData>* minValueMostStreamedTree = mostStreamedArtistTree->getMinNode();
    AVLNode<sameArtistTreeData>* minValueSongIndexForMinArtist = minValueMostStreamedTree->getData().artist_song_index->getMinNode();

    artists[0] = minValueMostStreamedTree->getData().artistID;
    songs[0] = minValueSongIndexForMinArtist->getData().songIndex;

    //TODO implement rest of function using inorder scan

}

/**
 * ends execution by releasing all stored memory of Data Structure
 */
void MusicManager::EndProgram() {
    //TODO implement proper deletion of Data Structure
    BasicNode<recommendListData>* station = recommendList->getHead();
    while (station != NULL) {
        AVLTree<sameNumTreeData>* sameNumTree = station->getData().sameNumTree;
        //iterate over all nodes in tree
            //for each node delete the tree associated with it

        //delete the tree
        station = station->getNext();
        //delete prev node
    }

    //delete artist tree (taking care to delete array for each node)

}



#endif //WET1_MUSICMANAGER_H
