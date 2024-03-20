#include <osbind.h>
#include "PSG.H"
#include "EFFECTS.H"

void play_gunshot(){
	write_psg(6, 0x0F);
	write_psg(7, 0x07); /* <-  Have to modify to make use of the enable channel funtions 
	write_psg(8, 0x10);
	write_psg(9, 0x10);
	write_psg(10, 0x10);
	write_psg(12, 0x10);
	write_psg(13, 0x00);
  
 /*
 	set_noise(0x0F);
	
	enable_channel(CHANNEL_A, TONE_A_OFF, NOISE_ON);

	enable_channel(CHANNEL_B, TONE_A_OFF, NOISE_ON);
	enable_channel(CHANNEL_C, TONE_A_OFF, NOISE_ON);

	set_volume(CHANNEL_A, 0x10);
	set_volume(CHANNEL_B, 0x10);
	set_volume(CHANNEL_C, 0x10);
	
	set_envelop(NONE, 0x1000);
*/
	return; 
};

void play_flaps(){

};

void play_explosion(){
	set_noise(0x1F);
  
	write_psg(MIXER_IO, 0x07); /* Have to modify to make use of the enable channel funtions */
  
	set_volume(A_vol, 0x10);
	set_volume(B_vol, 0x10);
	set_volume(C_vol, 0x10);

	write_psg(ENVELOPE_COARSE, 0x38);
	write_psg(ENVELOPE_SHAPE, 0x00);
	return;
};