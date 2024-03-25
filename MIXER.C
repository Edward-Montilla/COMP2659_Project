#include "PSG.H"
#include <osbind.h>
#include <stdio.h>
#include "EVENTS.H"
#include "EFFECTS.H"

#define quarter 35

int notes[] = { 
  C_FLT ,
  C_SHR ,
  D_FLT ,
  D_SHR ,
  E_FLT ,
  F_FLT ,
  F_SHP ,
  G_FLT ,
  G_SHP ,
  A_FLT ,
  A_SHP ,
  B_FLT
};

int main() {

  /* proof of concept for writing songs, note: E flat is held for a second and 
    switched to F sharp after ~5 seconds */ 
  int n = 0, hold = 0;
  UINT32 tiks = 0; 
  clock_timer(&tiks);

  enable_channel(CHANNEL_B, TONE_ON, NOISE_OFF);
  set_volume(B_vol, 10);

  while (n < 13){
      set_tone(CHANNEL_B, notes[n]);
      while((tiks < hold)){ /* 350 ticks is ~ 10 seconds */
      printf("tiks =  %lu\n", tiks);
      clock_timer(&tiks);
      }
      n++;
      hold += 21;
  };
/*
  while (!Cconis()) /* tone now playing, await key 
    ;

  Cnecin();
*/
  stop_sound();
  
  return 0;
}
