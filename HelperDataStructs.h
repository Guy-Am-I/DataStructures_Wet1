//
// Created by Guy Steinberg on 5/14/20.
//

#ifndef WET1_HELPERDATASTRUCTS_H
#define WET1_HELPERDATASTRUCTS_H

#include "AVLTree.h"

//Data types for all 4 different Data Structures we use in this problem
//This way the tree and list data structures can stay as a generic template
//and thus only the data changes to our needs
typedef struct sameArtistTreeData {
    int songIndex;
    sameArtistTreeData(int songIndex_) {
        songIndex = songIndex_;
    };

    const int getDataToCompare() const {return songIndex; }
} sameArtistTreeData;

typedef struct sameNumTreeData{
    int artistID;
    AVLTree<sameArtistTreeData>* artist_song_index;

    sameNumTreeData(int artistID_, AVLTree<sameArtistTreeData>* artist_song_index_){
        artistID = artistID_;
        artist_song_index = artist_song_index_;
    }
    const int getDataToCompare() const  {return artistID; }
} sameNumTreeData;


typedef struct recommendListData {
    int numberOfStreams;
    AVLTree<sameNumTreeData>* sameNumTree; //AVL tree representing all artists with songs having same number of streams

    recommendListData(int numberOfStreams_, AVLTree<sameNumTreeData>* sameNumTree_) {
        numberOfStreams = numberOfStreams_;
        sameNumTree = sameNumTree_;
    }

    const int getDataToCompare() const {return numberOfStreams; }
} recommendListData;

typedef struct artistTreeData {
    int artistID; //unique artist number
    int numOfSongs;
    BasicNode<recommendListData>** songs; //pointer to song_array

    artistTreeData(int artistID_, int numOfSongs_, BasicNode<recommendListData>** songs_){
        artistID = artistID_;
        numOfSongs = numOfSongs_;
        songs = songs_;
    }
    const int getDataToCompare() const {return artistID; }
} artistTreeData;



#endif //WET1_HELPERDATASTRUCTS_H
