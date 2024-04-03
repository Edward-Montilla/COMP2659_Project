#include <osbind>
#include "PSG.H"
#include "MUSIC.H"
#include "TYPES.H"
#include "INPUT.H"

Notes opening[] = {
	/* the opening theme of the game */
	{G_FLT, quarter},
	{F_SHP, quarter},
	{E_FLT, quarter},
	{D_FLT, quarter},
	{C_FLT, quarter},
	{D_FLT, quarter},
	{E_FLT, quarter},
	{F_SHP, quarter},
	{G_FLT, quarter}
};

Notes laugh[] ={
	{D_FLT, eight},
	{G_FLT, eight},
	{B_FLT, eight},
	{A_FLT, eight},
	{G_FLT, eight},
	{D_FLT, eight},
};

void start_music(){
	set_tone(A, opening[0]);
	/* enable channel A*/
	return;
};

void update_music(UINT32 time_elapsed){


};

void start_dog_laugh(){


};

void update_dog_laugh(UINT32 time_elapsed){

};

void stop_music(){
	stop_sound();
	return;
}

