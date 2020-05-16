//
// Created by Guy Steinberg on 5/14/20.
//
#include "library1.h"
#include "MusicManager.h"

void *Init() {
    MusicManager *DS = new MusicManager();
    return (void *)DS;
}
StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    if(DS == NULL) return INVALID_INPUT;
    return ((MusicManager *)DS)-> AddDataCenter(artistID, numOfSongs);
}

StatusType RemoveArtist(void *DS, int artistID) {
    if (DS == NULL) return INVALID_INPUT;
    return  ((MusicManager *)DS)->RemoveData(artistID);
}

StatusType AddToSongCount(void *DS, int artistID, int songID) {
    if (DS == NULL) return INVALID_INPUT;
    return ((MusicManager*)DS) -> ArtistSongStreamed(artistID, songID);
}

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams) {
    if (DS == NULL) return INVALID_INPUT;
    return ((MusicManager*) DS) -> AmountOfStreams(artistID, songID, streams);
}

StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs){
    if (DS == NULL) return INVALID_INPUT;
    return ((MusicManager*) DS) -> GetRecommendations(numOfSongs, artists, songs);
}

void Quit(void** DS) {
    if (DS == NULL) return;
    delete ((MusicManager*) *DS);
    *DS =NULL;
}
