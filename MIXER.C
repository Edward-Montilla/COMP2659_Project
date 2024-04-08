#include "PSG.H"
#include <osbind.h>
#include <stdio.h>
#include "EVENTS.H"
#include "EFFECTS.H"
#include "MUSIC.H"

#define quarter 35

int main() {

	UINT32 time_then, time_elapsed, time_now;
	clock_timer(&time_then);
	clock_timer(&time_now);
	printf("Current time == %ld\n",time_now);

	start_music();

	while(!Cconis()){;
		clock_timer(&time_now);
		time_elapsed = time_now - time_then;
		printf("Current time == %ld\n",time_elapsed);
		if(time_elapsed >= 1){
				update_music(time_elapsed);
				time_then = time_now;
		}
	}

	stop_sound();
	Cnecin();
	return 0;
}
