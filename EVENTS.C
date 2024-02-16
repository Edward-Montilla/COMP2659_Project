#include "EVENTS.H"

/*******************************************************************************
 * FUNCTION NAME: move_up_request                                              *
 *                                                                             *
 * PURPOSE: Requests a change of vertical position of the reticle              *
 *                                                                             *
 * INPUT: *reticle = pointer to structure of structure.                        *
 *                                                                             *
 * OUTPUT: no return value from function, the structure's change in y          *
 *          manipulated.                                                       *
 *                                                                             *
 * ASSUMPTION: Assumes that Reticle structure is instantiated.                 *
 *                                                                             *
 *******************************************************************************/
void move_up_request(Reticle *reticle) {
    reticle->dy += 1;
    move_reticle(reticle);
}

/*******************************************************************************
 * FUNCTION NAME: move_left_request                                            *
 *                                                                             *
 * PURPOSE: Requests a change of horizontal position of the reticle            *
 *                                                                             *
 * INPUT: *reticle = pointer to structure of structure.                        *
 *                                                                             *
 * OUTPUT: no return value from function, the structure's change in x          *
 *          manipulated.                                                       *
 *                                                                             *
 * ASSUMPTION: Assumes that Reticle structure is instantiated.                 *
 *                                                                             *
 *******************************************************************************/
void move_left_request(Reticle *reticle) {
    reticle->dx -= 1;
    move_reticle(reticle);
}

bool bounds_check(Reticle *reticle) {
    bool in_bounds = TRUE;

    if (reticle->x + reticle->width > 638 
    || reticle->y + reticle->height > 398)
        in_bounds = FALSE;

    return in_bounds;
}