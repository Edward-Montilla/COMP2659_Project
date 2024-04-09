#ifndef MUSIC_H
#define MUSIC_H

#include "TYPES.H"

/*******************************************************************************
 * STUDENT: Jaunie Williams, Edward Montilla                                   *
 *                                                                             *
 * COURSE: COMP2659 - COMPUTING MACHINERY II                                   *
 *                                                                             *
 * PROFESSOR: Marc Schroeder								                                   *
 * 																			                                       *
 * PURPOSE: Handles all music coordination.                                    *
 *                                                                             *
 *******************************************************************************/

/* Durations based on 4-4 time measure at 120 bmp */

#define sixteenth	4
#define eight 		8
#define quarter		16
#define half		32
#define whole		64


/* A 'song' will be an array of Note data types
  that encapsulate pitch and duration */
typedef struct {
  int pitch;    /* the pitch of the note */
  int duration; /* the duration of the  note */
} Note;

void start_music();
void update_music(UINT32 time_elapsed);
void start_dog_laugh();
void update_laugh(UINT32 time_elapsed);
void stop_music();

#endif
