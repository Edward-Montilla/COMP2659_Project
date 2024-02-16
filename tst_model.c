#include "MODEL.H"
#include <stdio.h>
#include <stdlib.h>

int main() {

  char intro[] = "This is a test for the models.c functions.";
  char init_reticle[] = "Initializing Reticle object...";

  printf("%s\n", intro);
  printf("%s\n", init_reticle);

  Reticle *reticle = malloc(sizeof(Reticle));

  reticle->x = 0;
  reticle->y = 0;
  reticle->dx = 0;
  reticle->dy = 0;

  char init_mallard[] = "Initializing Mallard object...";

  printf("%s\n", init_mallard);

  Mallard *mallard = malloc(sizeof(Mallard));

  mallard->x = 0;
  mallard->y = 0;
  mallard->dx = 0;
  mallard->dy = 0;

  char drive_mallard[] = "Driving Mallard object 4 += x, 4 += y...";
  printf("%s\n", drive_mallard);

  mallard->x += 4;
  mallard->y += 4;

  printf("New Mallard object position: %d, %d\n", mallard->x, mallard->y);

  char drive_reticle[] = "Driving Retile object 7 += x, 3 += y...";

  reticle->x += 7;
  reticle->y += 3;

  printf("New reticle object position: %d, %d\n", reticle->x, reticle->y);

  free(reticle);
  free(mallard);
  return 0;
}
