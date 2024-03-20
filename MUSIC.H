#ifndef MUSIC_H
#define MUSIC_H

#include "TYPES.H"

/* Durations based on 4-4 time measure at 120 bmp */
#define sixteenth 4
#define eight 
#define quarter
#define half
#define whole

/* A 'song' will be an array of Notes data types 
  that encapsulate pitch and duration */
typedef struct {
	int pitch;    /* the pitch of the note */
	int duration; /* the duration of the  note */
} Notes;

void start_music();
void update_music(UINT32 time_elapsed);
void start_dog_laugh();
void update_laugh(UINT32 time_elapsed);

#endif
