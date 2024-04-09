#ifndef EVENTS_H
#define EVENTS_H

/*******************************************************************************
 * STUDENT: Jaunie Williams, Edward Montilla                                   *
 *                                                                             *
 * COURSE: COMP2659 - COMPUTING MACHINERY II                                   *
 *                                                                             *
 * PROFESSOR: Marc Schroeder								                   *
 * 																			   *
 * PURPOSE: Communicates with effects and models to create synchronous and     *
 *         asynchronous game effects.                                          *
 *                                                                             *
 *******************************************************************************/

#include "MODEL.H"
#include "RENDERER.H"

/* Asynchronous Events */
void move_up_request(Reticle *reticle);
void move_down_request(Reticle *reticle);
void move_left_request(Reticle *reticle);
void move_right_request(Reticle *reticle);
void shoot_request(Reticle *reticle, Mallard *mallard);

/* Synchronous Events */
void clock_timer(UINT32 *count);
void mallard_move_request(Mallard *mallard);

/* Cascaded Events */
bool shoot_win_check(Mallard *target_a, Mallard *target_b);
bool time_lose_check(int timer);
bool bounds_check_enemy(Mallard *mallard);

UINT32 get_time();

#endif