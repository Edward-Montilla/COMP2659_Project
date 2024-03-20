#include <osbind.h>
#include <stdio.h>
#include "EVENTS.H"
#include "MODEL.H"

/*******************************************************************************
 * FUNCTION NAME: move_up_request                                              *
 *                                                                             *
 * PURPOSE: Requests a change of vertical position of the reticle and then     *
 *         resets the reticle's velocity at the end.                           *
 *          If the requested position is out of bounds, the position will      *
 *         restrict movement.                                                  *
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
    reticle->dy -= 4;
    move_reticle(reticle);

    if (!bounds_check(reticle)) {
        Cconws("Out of bounds!");
        reticle->dy += 6;
        move_reticle(reticle);
    }
    
    reticle->dy = 0;
}

/*******************************************************************************
 * FUNCTION NAME: move_down_request                                            *
 *                                                                             *
 * PURPOSE: Requests a change of vertical position of the reticle and then     *
 *         resets the reticle's velocity at the end.                           *
 *          If the requested position is out of bounds, the position will      *
 *         restrict movement.                                                  *
 *                                                                             *
 * INPUT: *reticle = pointer to structure of structure.                        *
 *                                                                             *
 * OUTPUT: no return value from function, the structure's change in y          *
 *          manipulated.                                                       *
 *                                                                             *
 * ASSUMPTION: Assumes that Reticle structure is instantiated.                 *
 *                                                                             *
 *******************************************************************************/
void move_down_request(Reticle *reticle) {
    reticle->dy += 4;
    move_reticle(reticle);

    if (!bounds_check(reticle)) {
        Cconws("Out of bounds!");
        reticle->dy -= 6;
        move_reticle(reticle);
    }
    
    reticle->dy = 0;
}

/*******************************************************************************
 * FUNCTION NAME: move_left_request                                            *
 *                                                                             *
 * PURPOSE: Requests a change of horizontal position of the reticle and then   *
 *         resets the reticle's velocity at the end.                           *
 *          If the requested position is out of bounds, the position will      *
 *         restrict movement.                                                  *
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
    reticle->dx -= 4;
    move_reticle(reticle);

    if (!bounds_check(reticle)) {
        Cconws("Out of bounds!");
        reticle->dx += 6;
        move_reticle(reticle);
    }

    reticle->dx = 0;
}

/*******************************************************************************
 * FUNCTION NAME: move_right_request                                           *
 *                                                                             *
 * PURPOSE: Requests a change of horizontal position of the reticle and then   *
 *         resets the reticle's velocity at the end.                           *
 *          If the requested position is out of bounds, the position will      *
 *         restrict movement.                                                  *
 *                                                                             *
 * INPUT: *reticle = pointer to structure of structure.                        *
 *                                                                             *
 * OUTPUT: no return value from function, the structure's change in x          *
 *          manipulated.                                                       *
 *                                                                             *
 * ASSUMPTION: Assumes that Reticle structure is instantiated.                 *
 *                                                                             *
 *******************************************************************************/
void move_right_request(Reticle *reticle) {
    reticle->dx += 4;
    move_reticle(reticle);

    if (!bounds_check(reticle)) {
        Cconws("Out of bounds!");
        reticle->dx -= 6;
        move_reticle(reticle);
    }

    reticle->dx = 0;
}

/*******************************************************************************
 * FUNCTION NAME: clock_timer                                                  *
 *                                                                             *
 * PURPOSE: Accesses the clock to and synchronizes it with the game.           *
 *                                                                             *
 * INPUT: *count = a pointer to an int that represents the in-game timer.      *
 *                                                                             *
 * OUTPUT: no return value from function, in-game timer is reduced by one.     *
 *                                                                             *
 * ASSUMPTION: Assumes that count is dereferenced.                             *
 *                                                                             *
 *******************************************************************************/
void clock_timer(UINT32 *count) {
    UINT32 timeThen, timeNow, timeElapsed;
    timeNow = get_time();
    timeElapsed = timeNow - timeThen;

    if (timeElapsed > 0) {
        timeThen = timeNow;
        (*count) += 1;
    }
}

/*******************************************************************************
 * FUNCTION NAME: get_time                                                     *
 *                                                                             *
 * PURPOSE: Accesses the Atari ST's clock.                                     *
 *                                                                             *
 * OUTPUT: timeNow = the current value of the clock.                           *
 *                                                                             *
 * ASSUMPTION: Assumes the clock is not broken.                                *
 *                                                                             *
 *******************************************************************************/

UINT32 get_time() {
  long old_ssp;
  UINT32 timeNow;
  long *timer = (long *)0x462;

  old_ssp = Super(0);
  timeNow = *timer;
  Super(old_ssp);

  return timeNow;
}

/*******************************************************************************
 * FUNCTION NAME: mallard_move_request                                         *
 *                                                                             *
 * PURPOSE: Moves mallard object in a square flight pattern by slowly changing *
 *         it's velocity.                                                      *
 *          With this current pattern, mallards cannot collide of go off       *
 *         screen.                                                             *
 *                                                                             *
 * INPUT: *mallard = pointer to structure of structure.                        *
 *                                                                             *
 * OUTPUT: no return value from function, the structure's change in x and y    *
 *          manipulated.                                                       *
 *                                                                             *
 * ASSUMPTION: Assumes that Mallard structure is instantiated.                 *
 *                                                                             *
 *******************************************************************************/
void mallard_move_request(Mallard *mallard) {
    if (mallard->y > 350) mallard->dx -= 4;
    if (mallard->y < 50) mallard->dx += 4;
    if (mallard->x < 50) mallard->dy -= 4;
    if (mallard->x > 590) mallard->dy += 4;

    move_mallard(mallard);
    mallard->dx = 0;
    mallard->dy = 0;
}


/*******************************************************************************
 * FUNCTION NAME: time_lose_check                                              *
 *                                                                             *
 * PURPOSE: Checks the game's in-game clock for the lose condition. (Timer = 0)*
 *                                                                             *
 * INPUT: timer = an int to represent the in-game timer.                       *
 *                                                                             *
 * OUTPUT: returns FALSE if the in-game timer is not 0, returns TRUE otherwise.*
 *                                                                             *
 * ASSUMPTION:                                                                 *
 *                                                                             *
 *******************************************************************************/
bool time_lose_check(int timer) {
    bool time_out = FALSE;
    
    if (timer == 0) time_out = TRUE;

    return time_out;
}

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
 * ASSUMPTION:                                                                 *
 *                                                                             *
 *******************************************************************************/
bool bounds_check(Reticle *reticle) {
    bool in_bounds = TRUE;

    if (reticle->x <= 1
    || reticle->x + reticle->width >= 638
    || reticle->y <= 1 
    || reticle->y + reticle->height >= 398)
        in_bounds = FALSE;

    return in_bounds;
}

/* Uneeded at this stage, reference mallard_move_request documentation */
/* bool bounds_check_enemy(Mallard *mallard) {
    bool in_bounds = TRUE;

    if (mallard->x <= 1
    || mallard->x + mallard->width >= 638
    || mallard->y <= 1 
    || mallard->y + mallard->height >= 398)
        in_bounds = FALSE;

    return in_bounds;
} */ 