#include <osbind.h>
#include <stdio.h>

#include "TYPES.H"
#include "FONT.H"
#include "RASTER.H"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define FONT_HEIGHT 8

int main() { /* prints all the fonts in succession */
  int x,y;

  void *base = Physbase();
  int text = 0;

  printf("Prints all possible fonts in the font.h file \n");

  for (y = 0; y < SCREEN_HEIGHT; y += FONT_HEIGHT){
    for (x = 0; x < SCREEN_WIDTH; x += sizeof(UINT8)){
      plot_text(base, x, y, font, text);
      text++;
    }
  }

  return 0;
}
