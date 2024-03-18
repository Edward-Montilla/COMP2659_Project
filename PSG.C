#include "PSG.H"
#include "TYPES.H"
#include <osbind.h>

#include <stdio.h>

volatile char *PSG_select = SELECT_REG;
volatile char *PSG_write = WRITE_REG;

/*******************************************************************************
 * FUNCTION NAME: write_psg                                                    *
 *                                                                             *
 * PURPOSE: writes the value to the given register                             *
 *                                                                             *
 * INPUT: 'reg' an int pertaining to the register number of the interface      *
 *        'vav' an unsiged 8 bit integer pertaining to the value to be         *
 *            written to the register selected                                 *
 *                                                                             *
 * OUTPUT: no return value from function, places value onto mememory address   *
 *                                                                             *
 * ASSUMPTION: Assumes that there is a YM2149 chip and its control registers   *
 *             are mapped at addresses:                                        *
 *                             select register: 0xFF8800                       *
 *                              write register: 0xFF8802                       *
 *******************************************************************************/
void write_psg(int reg, UINT8 val)
{
	long og_spr = Super(0);
	if (0 <= reg && reg <= 15 && 0 <= val && val <= 255){
		*PSG_select = reg;
		*PSG_write = val;
	}
	Super(og_spr);
	return;
}

/*******************************************************************************
 * FUNCTION NAME: read_psg                                                     *
 *                                                                             *
 * PURPOSE: reads value writen onto a specified register                       *
 *                                                                             *
 * INPUT: 'reg' an int pertaining to the register number of the interface      *
 *                                                                             *
 * OUTPUT: an unsigned 8 bit number pertaining to what was writen to           *
 *         the given register                                                  *
 *                                                                             *
 * ASSUMPTION: Assumes that there is a YM2149 chip and its control registers   *
 *             are mapped at addresses:                                        *
 *                             select register: 0xFF8800                       *
 *                              write register: 0xFF8802                       *
 *******************************************************************************/
int read_psg(int reg)
{
	long og_spr;
	int val = -1;
	if (0 <= reg && reg <= 15){
		long og_spr = Super(0);
		*PSG_select = reg;
		val = *PSG_write;
		Super(og_spr);
	}
	return val;
}

/*******************************************************************************
 * FUNCTION NAME: set_tone                                                     *
 *                                                                             *
 * PURPOSE: writes the tone to the given channel                               *
 *                                                                             *
 * INPUT: 'channel' an int pertaining to the register number of the interface  *
 *             Channels are: 0 = A, 1 = B, 2 = C                               *
 *        'tunning' an integer pertaining to the value to be written to the    *
 *         channel selected                                                    *
 *                                                                             *
 * OUTPUT: no return value from function, places value onto mememory address   *
 *                                                                             *
 * ASSUMPTION: Assumes that there is a YM2149 chip and its control registers   *
 *             are mapped at addresses:                                        *
 *                             select register: 0xFF8800                       *
 *                              write register: 0xFF8802                       *
 *******************************************************************************/
void set_tone(int channel, int tunning)
{
	int fine = tunning;
	int coarse = tunning;

	if (0 <= channel && channel <= 2 && 0 <= tunning && tunning <= 4096){
		fine &= 0x00FF; /* capture the bottom 8 bits of 12 through masking */
		coarse >= 8;    /* capture the top 4 bits of 12 through right shifting */
		
		switch (channel){
			case CHANNEL_A:
				write_psg(A_fine, fine);
				write_psg(A_coarse, coarse);
				break;
			
			case CHANNEL_B:
				write_psg(B_fine, fine);
				write_psg(B_coarse, coarse);
				break;
			
			case CHANNEL_C:
				write_psg(C_fine, fine);
				write_psg(C_coarse, coarse);
				break;
			
			default:
				break;
		}
	}
	return;
};

/*******************************************************************************
 * FUNCTION NAME: set_volume                                                   *
 *                                                                             *
 * PURPOSE: sets volume of channel to given value                              *
 *                                                                             *
 * INPUT: 'channel' an int pertaining to the channel number of the interface   *
 *        'volume' an int pertaining to the level of volume.                   *
 *                                                                             *
 * OUTPUT: no return value from function, places value onto mememory address   *
 *                                                                             *
 * ASSUMPTION: Assumes that there is a YM2149 chip and its control registers   *
 *             are mapped at addresses:                                        *
 *                             select register: 0xFF8800                       *
 *                              write register: 0xFF8802                       *
 *******************************************************************************/
void set_volume(int channel, int volume){

	if (0x08 <= channel && channel <= 0x0A && 0 <= volume && volume <= 31){
		write_psg(channel, volume);
	}
	return;
};

/*******************************************************************************
 * FUNCTION NAME: enable_channel                                               *
 *                                                                             *
 * PURPOSE: ennables tone or noise segment of a given channel                  *
 *                                                                             *
 * INPUT: 'channel' an int pertaining to the channel to be enabled/disabled    *
 *        'tone_on' int pertaining to the state of the tone of given channel   *
 *        'noise_on' int pertaining to the state of the noise of given channel *
 *                                                                             *
 * OUTPUT: no return value from function, places value onto mememory address   *
 *                                                                             *
 * ASSUMPTION: Assumes that there is a YM2149 chip and its control registers   *
 *             are mapped at addresses:                                        *
 *                             select register: 0xFF8800                       *
 *                              write register: 0xFF8802                       *
 *            on = 1, off = 0                                                  *
 *******************************************************************************/
void enable_channel(int channel, int tone_on, int noise_on){
	int mask_tune;
	mask_tune  = read_psg(MIXER_IO);
	if (0 <= tone_on && tone_on <= 1 && 0 <= noise_on && noise_on <= 1){
		/* mask_tune assigned with  current config of Mixer register */
		 
		printf("MIXER_IO current settings = %d\n", mask_tune);
		
		switch (channel){
			case CHANNEL_A:
				/* This is where you write the code is you were a good programmer and liked putting in the work */
				break;
			
			case CHANNEL_B:
				break;
			
			case CHANNEL_C:
				break;
			
			default:
				break;
		}
	}
	return;
}

/*******************************************************************************
 * FUNCTION NAME: stop_sound                                                   *
 *                                                                             *
 * PURPOSE: stops sound from all registers                                     *
 *                                                                             *
 * INPUT: none                                                                 *
 *                                                                             *
 * OUTPUT: no return value from function, places value onto mememory address   *
 *                                                                             *
 * ASSUMPTION: Assumes that there is a YM2149 chip and its control registers   *
 *             are mapped at addresses:                                        *
 *                             select register: 0xFF8800                       *
 *                              write register: 0xFF8802                       *
 *******************************************************************************/
void stop_sound(){
	int reg;
	for (reg = 0; reg <= 0xF; reg++){
		if(reg == 7){
			write_psg(MIXER_IO,0x3F); /* Plug all channels */
		}
		else{
		write_psg(reg, 0); /* reduce all pitch data to 0 */
		}
	}
};

/*******************************************************************************
 * FUNCTION NAME: set_noise                                                    *
 *                                                                             *
 * PURPOSE: loads noise register with  a 5 bit values                          *
 *                                                                             *
 * INPUT: 'tuning' an intger value to be written to the noise register         *
 *                                                                             *
 * OUTPUT: no return value from function, places value onto mememory address   *
 *                                                                             *
 * ASSUMPTION: Assumes that there is a YM2149 chip and its control registers   *
 *             are mapped at addresses:                                        *
 *                             select register: 0xFF8800                       *
 *                              write register: 0xFF8802                       *
 *******************************************************************************/
void set_noise(int tuning){
	if (0 <= tuning && tuning <= 31){
		write_psg(NOISE, tuning);
	}
	return;
};

/*******************************************************************************
 * FUNCTION NAME: set_envelop                                                  *
 *                                                                             *
 * PURPOSE: Sets envelop shape and values to YM3149                            *
 *                                                                             *
 * INPUT: 'shape' designates the register with the given shape,                *
 *                only one shape can be set at a time                          *
 *                                                                             *
 *        'sustain' a 16 bit value to be split up and loaded into the          *
 *                fine and coarse envelop registers                            *
 *                                                                             *
 * OUTPUT: no return value from function, places value onto mememory address   *
 *                                                                             *
 * ASSUMPTION: Assumes that there is a YM2149 chip and its control registers   *
 *             are mapped at addresses:                                        *
 *                             select register: 0xFF8800                       *
 *                              write register: 0xFF8802                       *
 *******************************************************************************/
void set_envelop(int shape, unsigned int sustain){
	
	int fine = 0x00FF & sustain;
	int coarse = sustain >> 8;

	/* Make this not so dependent on current input,
	dont let it clear other bits sisnce you can only
	turn on things one at a time asshole*/

	switch (shape){
		case HOLD:
			write_psg(ENVELOPE_SHAPE, 1);
			write_psg(ENVELOPE_FINE, fine);
			write_psg(ENVELOPE_COARSE, coarse);
			break;

		case ALT:
			write_psg(ENVELOPE_SHAPE, 2);
			write_psg(ENVELOPE_FINE, fine);
			write_psg(ENVELOPE_COARSE, coarse);
			break;

		case ATT:
			write_psg(ENVELOPE_SHAPE, 4);
			write_psg(ENVELOPE_FINE, fine);
			write_psg(ENVELOPE_COARSE, coarse);
			break;

		case CONT:
			write_psg(ENVELOPE_SHAPE, 8);
			write_psg(ENVELOPE_FINE, fine);
			write_psg(ENVELOPE_COARSE, coarse);
			break;
	}
	return;
};