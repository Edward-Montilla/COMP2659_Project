#include <stdio.h>
#include "INPUT.H"

void read_key(int key, Reticle *ret) {
    switch (key)
    {
    case 'w':
        move_up_request(ret);
        break;
    case 's':
        move_down_request(ret);
        break;
    case 'a':
        move_left_request(ret);
        break;
    case 'd':
        move_right_request(ret);
        break;
    case ' ':
        play_gunshot();
        break;
    case 'g':
        play_explosion();
        break;
    
    default:
        break;
    }
}