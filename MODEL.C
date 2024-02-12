#include "MODEL.H"

/*******************************************************************************
 * FUNCTION NAME: move_reticle                                                 *
 *                                                                             *
 * PURPOSE: Changes the position of the reticle                                *
 *                                                                             *
 * INPUT: *reticle = pointer to structure of structure.                        *
 *                                                                             *
 * OUTPUT: no return value from function, position is changed in the           *
 *          structure fields.                                                  *
 *                                                                             *
 * ASSUMPTION: Assumes that Reticle structure is instantiated.                 *
 *                                                                             *
 *******************************************************************************/
void move_reticle(Reticle *reticle) {
  reticle->x += reticle->dx;
  reticle->y += reticle->dy;
};

/*******************************************************************************
 * FUNCTION NAME: move_mallard                                                 *
 *                                                                             *
 * PURPOSE: Changes the position of the mallard                                *
 *                                                                             *
 * INPUT: *mallard = pointer to structure of structure.                        *
 *                                                                             *
 * OUTPUT: no return value from function, position is changed in the           *
 *          structure fields.                                                  *
 *                                                                             *
 * ASSUMPTION: Assumes that Mallard structure is instantiated.                 *
 *                                                                             *
 *******************************************************************************/
void move_mallard(Mallard *mallard) {
  if (mallard->is_dead)
    return;

  mallard->x += mallard->dx;
  mallard->y += mallard->dy;
};

/*******************************************************************************
 * FUNCTION NAME: is_hit                                                       *
 *                                                                             *
 * PURPOSE: Checks coordinate of two objects and returns true if hit           *
 *                                                                             *
 * INPUT: *mallard = pointer to structure                                      *
 *        *reticle = pointer to structure                                      *
 *                                                                             *
 * OUTPUT: no return value from function, conditionally change                 *
 *          is_dead flag in mallard sturcture                                  *
 *                                                                             *
 * ASSUMPTION: Assumes that sturctures are in play                             *
 *                                                                             *
 *******************************************************************************/
bool is_hit(Reticle *reticle, Mallard *mallard) {
  bool hit = false;
  if (reticle->x == mallard->x && reticle->y == mallard->y) {
    hit = true;
  
/* change dead status of mallard; make it so that tolerance for hits +- half tha area  
    Implement AABB algorithm in 2D
*/
  }
  return hit;
};
