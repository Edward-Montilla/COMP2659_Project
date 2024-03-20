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
  if (mallard->is_dead == TRUE) return;

  mallard->x += mallard->dx;
  mallard->y += mallard->dy;
};

/*******************************************************************************
 * FUNCTION NAME: is_hit                                                       *
 *                                                                             *
 * PURPOSE: Checks coordinate of two objects and returns true if hit           *
 *        This funtion uses an AABB collision algorithm found on amanotes [1]  *
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
/*bool is_hit(Reticle &reticle, Mallard &mallard) {
  bool hit = FALSE;
  
  int left = mallard.x - (reticle.x + reticle.width);
  int right = (mallard.x + mallard.width) - reticle.x;
  int top = (mallard.y + mallard.height) - reticle.y;
  int bottom = mallard.y - (reticle.y + reticle.height);

  if (left > 0 || right < 0 || top < 0 || bottom > 0) hit = TRUE;
  
  return hit;
}; 

/* Luu The Vinh. "Using Swept AABB to detect and process collision." amanotes.com.
  https://www.amanotes.com/post/using-swept-aabb-to-detect-and-process-collision#:~:text=What%20is%20AABB%3F,with%20each%20other%20or%20not
  (accessed Feb. 14, 2024) */