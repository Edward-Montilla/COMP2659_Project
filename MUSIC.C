#include "INPUT.H"
#include "MUSIC.H"
#include "PSG.H"
#include "TYPES.H"
#include <osbind.h>
#include <stdio.h>


#define OPENING_SIZE 8
#define LAUGH_SIZE 	7

Notes opening[] = {
	/* the opening theme of the game */
	{G_FLT, half}, {F_SHP, half}, {E_FLT, half},
	{D_FLT, half}, {C_FLT, half}, {D_FLT, half},
	{E_FLT, half}, {F_SHP, half}, {G_FLT, half}};

Notes laugh[] = {
	{D_FLT, eight}, {G_FLT, eight}, {B_FLT, eight},
	{A_FLT, eight}, {G_FLT, eight}, {D_FLT, eight},
};

int current_note, duration;

void start_music() {
	set_tone(CHANNEL_B, opening[0].pitch);
	printf("fine is set %d, coarse is set %d\n", read_psg(B_fine), read_psg(B_coarse));
	enable_channel(CHANNEL_B, TONE_ON, NOISE_OFF);
	printf("Channel B enabled! %d\n", read_psg(MIXER_IO));
	set_volume(B_vol, 15);
	printf("Volume set to %d! \n", read_psg(B_vol));
	current_note = 0;
	return;
};

void update_music(UINT32 time_elapsed){
	/* Repeat if end */
	if(current_note == OPENING_SIZE){
		printf("HELP UPDATE REPEAT! \n");
		current_note = 0;
		set_tone(CHANNEL_B, opening[current_note].pitch);
	}
	/* keep playing same note */
	if(time_elapsed  < opening[current_note].duration){
		printf("HELP UPDATE same note! \n");
		set_tone(CHANNEL_B, opening[current_note].pitch);
	}
	/* play next note */
	else{
		printf("HELP UPDATE next note! \n");
		current_note++;
		set_tone(CHANNEL_B, opening[current_note].pitch);
	}
	return;
};

void start_dog_laugh(){
	
};

void update_dog_laugh(UINT32 time_elapsed){
	
};
