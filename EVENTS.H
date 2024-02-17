#include "MODEL.H"

/* Asynchronous Events */
void move_up_request(Reticle *reticle);
void move_down_request(Reticle *reticle);
void move_left_request(Reticle *reticle);
void move_right_request(Reticle *reticle);
void shoot_request();
void pause();

/* Synchronous Events */
void temp_clock_tick();
void game_timer(int *timer);
void mallard_move_request(Mallard *mallard);

/* Cascaded Events */
bool shoot_win_check();
bool time_lose_check(int timer);
bool bounds_check(Reticle *reticle);
/* bool bounds_check_enemy(Mallard *mallard); */ /* Not needed yet */