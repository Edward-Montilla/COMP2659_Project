#include "MODEL.H"

/* Asynchronous Events */
void move_up_request(Reticle *reticle);
void move_down_request(Reticle *reticle);
void move_left_request(Reticle *reticle);
void move_right_request(Reticle *reticle);
void shoot_request();
void pause();

/* Synchronous Events */
void game_timer();
void mallard_move_request(Mallard *mallard);

/* Cascaded Events */
bool shoot_win_check();
bool time_lose_check();
bool bounds_check(Reticle *reticle);
bool bounds_check_enemy(Mallard *mallard);