#include "PSG.H"
#include "TYPES.H"
#include <osbind.h>

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
void write_psg(int reg, UINT8 val) {
  if (0 <= reg && reg <= 15 && 0 <= val && val <= 255) {
    *PSG_select = reg;
    *PSG_select = val;
  }
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
UINT8 read_psg(int reg) {
  if (0 <= reg && reg <= 15) {
    *PSG_select = reg;
  }
  return *PSG_write;
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
void set_tone(int channel, int tunning) {
  
  int fine = tunning;
  int coarse = tunning;

  if (0 <= channel && channel <= 2 && 0 <= tunning && tunning <= 4096) {
    fine &= 0x00FF; /* capture the bottom 8 bits of 12 through masking */
    coarse = coarse >> 8; /* capture the top 4 bits of 12 through right shifting */

    switch (channel) {
    case CHANNEL_A:
      write_psg(A_FINE,fine);
      /*-------------------*/
      write_psg(A_COARSE,coarse);
      break;
    case CHANNEL_B:
      write_psg(B_fine,fine);
      /*-------------------*/
      write_psg(B_coarse,coarse);
      break;
    case CHANNEL_C:
      write_psg(C_fine,fine);
      /*-------------------*/
      write_psg(C_coarse,coarse);
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
void set_volume(int channel, int volume) {
  if(0x08 <= channel && channel <= 0x0A && 0 <= volume && volume <= 15){
    write_psg(channel,volume);
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
 *******************************************************************************/
void enable_channel(int channel, int tone_on, int noise_on){
  int mask_tune = 0x3F;
  if(0 <= tone_on && tone_on <= 1 &&  0 <= noise_on  && noise_on <= 1){
    tone_on = tone_on ^ mask_tune;
    noise_on = noise_on ^ mask_tune;
    switch (channel) {
          case CHANNEL_A:
            tone_on = tone_on ^ mask_tune;
            noise_on = (noise_on << 3) ^ mask_tune;
            write_psg(MIXER_IO,tone_on);
            write_psg(MIXER_IO,noise_on);
            break;
          case CHANNEL_B:
            tone_on = (noise_on << 1) ^ mask_tune;
            noise_on = (noise_on << 4) ^ mask_tune;
            write_psg(MIXER_IO,tone_on);
            write_psg(MIXER_IO,noise_on);
            break;

          case CHANNEL_C:
            tone_on = (noise_on << 2) ^ mask_tune;
            noise_on = (noise_on << 5) ^ mask_tune;
            write_psg(MIXER_IO,tone_on);
            write_psg(MIXER_IO,noise_on);
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

  for(reg = 0; reg <= 0xF; reg++){
    write_psg(reg,0);
  }

};

/*******************************************************************************
 * FUNCTION NAME: set_noise                                                    *
 *                                                                             *
 * PURPOSE:                                                                    *
 *                                                                             *
 * INPUT:                                                                      *
 *                                                                             *
 * OUTPUT:                                                                     *
 *                                                                             *
 * ASSUMPTION: Assumes that there is a YM2149 chip and its control registers   *
 *             are mapped at addresses:                                        *
 *                             select register: 0xFF8800                       *
 *                              write register: 0xFF8802                       *
 *******************************************************************************/
void set_noise(int tuning) {
  /* write func here */
  return;
};

/*******************************************************************************
 * FUNCTION NAME: set_envelop                                                  *
 *                                                                             *
 * PURPOSE:          
 *                                                                             *
 * INPUT: 
 *                                                                             *
 * OUTPUT: 
 *                                                                             *
 * ASSUMPTION: Assumes that there is a YM2149 chip and its control registers   *
 *             are mapped at addresses:                                        *
 *                             select register: 0xFF8800                       *
 *                              write register: 0xFF8802                       *
 *******************************************************************************/
void set_envelop(int shape, unsigned int sustain) {
  /* write func here */
  return;
};
