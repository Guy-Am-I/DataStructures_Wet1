//
// Created by Guy Steinberg on 5/14/20.
//

#ifndef WET1_MUSICMANAGER_H
#define WET1_MUSICMANAGER_H
#pragma once
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

#endif //WET1_MUSICMANAGER_H
