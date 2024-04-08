#include <stdio.h>
#include "INPUT.H"

void read_key(int key, const Model *model) {
    switch (key)
    {
    case 'w':
        move_up_request(&(model->reticle));
        break;
    case 's':
        move_down_request(&(model->reticle));
        break;
    case 'a':
        move_left_request(&(model->reticle));
        break;
    case 'd':
        move_right_request(&(model->reticle));
        break;
    case ' ':
        shoot_request(&(model->reticle), &(model->mallards[0]));
        shoot_request(&(model->reticle), &(model->mallards[1]));
        break;
    default:
        break;
    }
}