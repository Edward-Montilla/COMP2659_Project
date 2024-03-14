#ifndef PSG_H
#define PSG_H

#include "TYPES.H"

#define C_FLT 0x1DE
#define C_SHR 0x1C3
#define D_FLT 0x1AA
#define D_SHR 0x192
#define E_FLT 0x17B
#define F_FLT 0x166
#define F_SHP 0x152
#define G_FLT 0x13F
#define G_SHP 0x12D
#define A_FLT 0x11C
#define A_SHP 0x10C
#define B_FLT 0x0FD

#define SELECT_REG 0xFF8800
#define WRITE_REG 0xFF8802

#define A_fine 0x00
#define A_coarse 0x01
#define B_fine 0x02
#define B_coarse 0x03
#define C_fine 0x04
#define C_coarse 0x05
#define NOISE 0x06
#define MIXER_IO 0x07
#define A_vol 0x08
#define B_vol 0x09
#define C_vol 0x0A
#define ENVELOPE_FINE 0x0B
#define ENVELOPE_COARSE 0x0C
#define ENVELOPE_SHAPE 0X0D
#define PORT_A 0x0E
#define PORT_B 0x0B

/* prototypes */

void write_psg(int reg, UINT8 val);
UINT8 read_psg(int reg);
void set_tone(int channel, int tunning);
void set_volume(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);
void stop_sound();
void set_noise(int tuning);
void set_envelop(int shape, unsigned int sustain);

#endif
