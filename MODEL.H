#ifndef MODEL_H
#define MODEL_H

/*******************************************************************************
 * STUDENT: Jaunie Williams, Edward Montilla                                   *
 *                                                                             *
 * COURSE: COMP2659 - COMPUTING MACHINERY II                                   *
 *                                                                             *
 * PROFESSOR: Marc Schroeder								                                   *
 * 																			                                       *
 * PURPOSE: Tracks all models and model-manipulating functions.                *
 *                                                                             *
 *******************************************************************************/

#include "TYPES.H"

typedef struct {
  /* position variables */
  unsigned int x, y;
  /* size variables*/
  const int width, height;
  /* displacement variables */
  int dx, dy;
} Reticle;

/* Clay Pigeon Bitmaps */
typedef struct {
  /* position variables */
  unsigned int x, y;
  /* size variables*/
  const int width, height;
  /* displacement variables */
  int dx, dy;
  /* out of play variable */
  bool is_dead;
  /* plays "animation" by cycling through bitmap */
  int phase;
} Mallard;

/* A structure for all models */
typedef struct {
  Reticle reticle;
  Mallard mallards[2];
} Model;

/* Prototypes */
void move_reticle(Reticle *reticle);
void move_mallard(Mallard *mallard);
bool is_hit(Reticle *reticle, Mallard *mallard);
bool bounds_check(Reticle *reticle);
void reticle_action(Reticle *reticle, bool is_horizontal, int change);
void mallard_action(Mallard *mallard, bool is_horizontal, int change);

/* bitmaps */
extern const UINT16 reticle_bitmap[];
extern const UINT16 mallard_bitmap[];
extern const UINT16 clay_pigeon_1[];
extern const UINT16 clay_pigeon_2[];
extern const UINT16 clay_pigeon_3[];
extern const UINT16 clay_pigeon_4[];
extern const UINT16 *clay_pigeon_bitmap[];
extern const UINT16 clay_pigeon_dead[];
extern const UINT8 starter_splashscreen[];
extern const UINT8 win_splashscreen[];

#endif