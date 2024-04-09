#include "EVENTS.H"
#include "INPUT.H"
#include "ISR.H"
#include "MODEL.H"
#include "MUSIC.H"

#include <osbind.h>
#include <stdio.h>

int main() {
  char pressed;
  load_vectors();

  /* busy wait for roughly 5 seconds */
  printf("Busy wait for ~5 seconds...\n");
  while (seconds < 5)
    ;

  printf("Calls to VBL ISR = %ld\n", VBL_calls);

  /* print the corresponding Keyboard input in ascii */
  while (pressed != 'q') {
    printf("\n");
  }

  restore_vectors();

  return 0;
}
