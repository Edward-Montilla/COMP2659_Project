#include <osbind.h>
#include "EVENTS.H"

/*******************************************************************************
 * FUNCTION NAME: move_up_request                                              *
 *                                                                             *
 * PURPOSE: Requests a change of vertical position of the reticle and then     *
 *         resets the reticle's velocity at the end.                           *
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
    reticle->dy -= 2;
    move_reticle(reticle);

    if (!bounds_check(reticle)) {
        Cconws("Out of bounds!");
        reticle->dy += 4;
        move_reticle(reticle);
    }
    
    reticle->dy = 0;
}

void move_down_request(Reticle *reticle) {
    reticle->dy += 2;
    move_reticle(reticle);

    if (!bounds_check(reticle)) {
        Cconws("Out of bounds!");
        reticle->dy -= 4;
        move_reticle(reticle);
    }
    
    reticle->dy = 0;
}

void move_left_request(Reticle *reticle) {
    reticle->dx -= 2;
    move_reticle(reticle);

    if (!bounds_check(reticle)) {
        Cconws("Out of bounds!");
        reticle->dx += 4;
        move_reticle(reticle);
    }

    reticle->dx = 0;
}

void move_right_request(Reticle *reticle) {
    reticle->dx += 2;
    move_reticle(reticle);

    if (!bounds_check(reticle)) {
        Cconws("Out of bounds!");
        reticle->dx -= 4;
        move_reticle(reticle);
    }

    reticle->dx = 0;
}

void game_timer(int *timer) {
    (*timer) -= 1;
}

/* flies in square shape */
void mallard_move_request(Mallard *mallard) {
    if (mallard->y > 350) mallard->dx -= 4;
    if (mallard->y < 50) mallard->dx += 4;
    if (mallard->x < 50) mallard->dy -= 4;
    if (mallard->x > 590) mallard->dy += 4;

    move_mallard(mallard);
    mallard->dx = 0;
    mallard->dy = 0;
}


bool bounds_check(Reticle *reticle) {
    bool in_bounds = TRUE;

    if (reticle->x <= 1
    || reticle->x + reticle->width >= 638
    || reticle->y <= 1 
    || reticle->y + reticle->height >= 398)
        in_bounds = FALSE;

    return in_bounds;
}

bool bounds_check_enemy(Mallard *mallard) {
    bool in_bounds = TRUE;

    if (mallard->x <= 1
    || mallard->x + mallard->width >= 638
    || mallard->y <= 1 
    || mallard->y + mallard->height >= 398)
        in_bounds = FALSE;

    return in_bounds;
}