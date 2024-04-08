#include <osbind.h>
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
  reticle->dx = 0;
  reticle->dy = 0;
};

/*******************************************************************************
 * FUNCTION NAME: bounds_check                                                 *
 *                                                                             *
 * PURPOSE: Checks the current position of the player (reticle) to ensure they *
 *         are in bounds.                                                      *
 *                                                                             *
 * INPUT: *reticle = pointer to structure of structure.                        *
 *                                                                             *
 * OUTPUT: returns TRUE if player is inbounds, returns FALSE otherwise.        *
 *                                                                             *
 * ASSUMPTION: Reticle is instantiated                                         *
 *                                                                             *
 *******************************************************************************/
bool bounds_check(Reticle *reticle) {
  bool in_bounds = TRUE;

  if (reticle->x + reticle->width < 20) {
    in_bounds = FALSE;
    reticle_action(reticle, TRUE, 11);
  } 
  
  if (reticle->x + reticle->width > 638) {
    in_bounds = FALSE;
    reticle_action(reticle, TRUE, -11);
  }
  if (reticle->y + reticle->height < 20) {
    in_bounds = FALSE;
    reticle_action(reticle, FALSE, 11);
  } 
  
  if (reticle->y + reticle->height > 398) {
    in_bounds = FALSE;
    reticle_action(reticle, FALSE, -11);
  }

  return in_bounds;
}

/*******************************************************************************
 * FUNCTION NAME: reticle_action                                               *
 *                                                                             *
 * PURPOSE: Intermediary step into moving player's unit.                       *
 *                                                                             *
 * INPUT: *reticle = pointer to structure of structure.                        *
 *        is_horizontal = TRUE if making a change in the x-value,              *
 *                  otherwise false.                                           *
 *        change = how much change in the given direction. (is_horizontal)     *
 *                                                                             *
 * OUTPUT: does not return anything, but it does move the reticle.             *
 *                                                                             *
 * ASSUMPTION: Reticle is instantiated                                         *
 *                                                                             *
 *******************************************************************************/
void reticle_action(Reticle *reticle, bool is_horizontal, int change) {
    switch (is_horizontal)
    {
    case TRUE:
        reticle->dx += change;
        break;
    case FALSE:
        reticle->dy += change;
        break;
    default:
        break;
    }

    move_reticle(reticle);
}

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
  if (mallard->is_dead == TRUE) {
    mallard->y -= mallard->dy;
    return;
  }

  mallard->x += mallard->dx;
  mallard->y += mallard->dy;
  mallard->dx = 0;
  mallard->dy = 0;
};

/*******************************************************************************
 * FUNCTION NAME: mallard_action                                               *
 *                                                                             *
 * PURPOSE: Intermediary step for moving enemy units.                          *
 *                                                                             *
 * INPUT: *reticle = pointer to structure of structure.                        *
 *        is_horizontal = TRUE if making a change in the x-value,              *
 *                  otherwise false.                                           *
 *        change = how much change in the given direction. (is_horizontal)     *
 *                                                                             *
 * OUTPUT: does not return anything, but it does move the reticle.             *
 *                                                                             *
 * ASSUMPTION: Reticle is instantiated                                         *
 *                                                                             *
 *******************************************************************************/
void mallard_action(Mallard *mallard, bool is_horizontal, int change) {
    switch (is_horizontal)
    {
    case TRUE:
        mallard->dx += change;
        break;
    case FALSE:
        mallard->dy += change;
        break;
    default:
        break;
    }

    move_mallard(mallard);
}

/*******************************************************************************
 * FUNCTION NAME: is_hit                                                       *
 *                                                                             *
 * PURPOSE: Checks coordinate of two objects and returns true if hit           *
 *        This funtion uses an AABB collision algorithm found on amanotes      *
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
  bool hit = FALSE;
  
  if (mallard->x < (reticle->x + reticle->width) &&
  (mallard->x + mallard->width) > reticle->x &&
  (mallard->y + mallard->height) > reticle->y &&
  mallard->y < (reticle->y + reticle->height)) {
    hit = TRUE;
  }
  
  return hit;
}; 

