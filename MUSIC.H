#ifndef MUSIC_H
#define MUSIC_H

#include "TYPES.H"

typedef struct{
	int pitch; /* the pitch of the note */
	int duration; /* the duration of the  note */
}Notes;

void start_music();
void update_music(UINT32 time_elapsed);

#endif
