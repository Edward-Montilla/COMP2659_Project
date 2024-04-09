#include <osbind.h>
#include <stdio.h>
#include "EVENTS.H"
#include "MODEL.H"
#include "EFFECTS.H"
#include "ISR.H"

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
    switch (bounds_check(reticle))
    {
    case TRUE:
        reticle_action(reticle, FALSE, -4);
        break;
    default:
        break;
    }
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
    switch (bounds_check(reticle))
    {
    case TRUE:
        reticle_action(reticle, FALSE, 4);
        break;
    default:
        break;
    }
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
    switch (bounds_check(reticle))
    {
    case TRUE:
        reticle_action(reticle, TRUE, -4);
        break;
    default:
        break;
    }
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
    switch (bounds_check(reticle))
    {
    case TRUE:
        reticle_action(reticle, TRUE, 4);
        break;
    default:
        break;
    }
}

/*******************************************************************************
 * FUNCTION NAME: shoot_request                                                *
 *                                                                             *
 * PURPOSE: Processes the after effects of a user shooting.                    *
 *                                                                             *
 * INPUT: *reticle = pointer to structure of structure.                        *
 *        *mallard = pointer to structure of structure.                        *
 *                                                                             *
 * OUTPUT: no return from function, this is the only function that can declare *
 *          the game's targets as dead.                                        *
 *                                                                             *
 * ASSUMPTION: Assumes Reticle and Mallard are instantiated.                   *
 *                                                                             * 
 *******************************************************************************/
void shoot_request(Reticle *reticle, Mallard *mallard) {
    play_gunshot();
    if (is_hit(reticle, mallard)) play_explosion();
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
    (*count) = VBL_calls;
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
    /* clay pigeon is dead and falls to bottom of screen */
    if (mallard->is_dead && bounds_check_enemy(mallard)) {
        mallard_action(mallard, FALSE, -4);
        return;
    }
    /* clay pigeon remains at the bottom of screen */
    if (mallard->is_dead) {
        return;
    }

    if (mallard->y > 350) mallard_action(mallard, TRUE, -4);
    if (mallard->y < 50) mallard_action(mallard, TRUE, 4);
    if (mallard->x < 50) mallard_action(mallard, FALSE, -4);
    if (mallard->x > 590) mallard_action(mallard, FALSE, 4);
}

/*******************************************************************************
 * FUNCTION NAME: shoot_win_check                                              *
 *                                                                             *
 * PURPOSE: Checks the status of both clay pigeons to assess the win condition.*
 *                                                                             *
 * INPUT: *target_a & *target_b = pointer to structure of structure.           *
 *                                                                             *
 * OUTPUT: returns a boolean. returns TRUE if both targets are declared dead.  *
 *          returns FALSE otherwise.                                           *
 *                                                                             *
 * ASSUMPTION: targets are instantiated.                                       *
 *                                                                             *
 *******************************************************************************/
bool shoot_win_check(Mallard *target_a, Mallard *target_b) {
    bool win = FALSE;

    if (target_a->is_dead && target_b->is_dead) {
        win = TRUE;
    }

    return win;
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
 * ASSUMPTION: timer is initiatlized.                                          *
 *                                                                             *
 *******************************************************************************/
bool time_lose_check(int timer) {
    bool time_out = FALSE;
    
    if (timer == 600) {
        time_out = TRUE;
    }

    return time_out;
}

/*******************************************************************************
 * FUNCTION NAME: bounds_check_enemy                                           *
 *                                                                             *
 * PURPOSE: Checks the current position of the clay pigeon to ensure they are  *
 *             in bounds.                                                      *
 *                                                                             *
 * INPUT: *mallard = pointer to structure of structure.                        *
 *                                                                             *
 * OUTPUT: returns TRUE if object is inbounds, returns FALSE otherwise.        *
 *                                                                             *
 * ASSUMPTION: Mallard is instantiated                                         *
 *                                                                             *
 *******************************************************************************/
bool bounds_check_enemy(Mallard *mallard) {
    bool in_bounds = TRUE;

    if (mallard->x + mallard->width <= 1
    || mallard->x + mallard->width >= 638
    || mallard->y + mallard->height <= 1 
    || mallard->y + mallard->height >= 370)
        in_bounds = FALSE;

    return in_bounds;
}

char read_IKBD(bool to_process){
    
    UINT32 code;
    char key;
    mask_interrupts();
    code = IKBD_buffer[head];
    code &= 0x000000FF; /* keep the low byte*/
    check_key(code, key);
    unmask_interrupts();
    
    return key;
}

static void check_key(UINT32 code, char key){
    switch (code){
    case ESC:
        key = 'q';
        break;
    
    case W:
        key = 'w';
        break;

    case A:
        key = 'a';
        break;

    case S:
        key = 's';
        break;

    case D:
        key = 'd';
        break;

    case SPC:
        key = ' ';
        break;

    default:
        key = 'N';
        break;
    }

}