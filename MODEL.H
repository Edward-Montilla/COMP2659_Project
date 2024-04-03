#ifndef MODEL_H
#define MODEL_H

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
void out_of_bounds_action(Reticle *reticle, bool is_horizontal, int change);

#endif