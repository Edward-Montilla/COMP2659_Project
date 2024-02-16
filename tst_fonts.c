#include "TYPES.H"
#include "FONT.H"
#include "RASTER.H"
#include <osbind.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define FONT_HEIGHT 8

int main() { /* prints all the fonts in succession */
  printf("Prints all possible fonts in the font.h file \n");

  void *base = Physbase();
  
  int x,y;
  int text = 0;

  for (y = 0; y < SCREEN_HEIGHT; y += FONT_HEIGHT){
    for (x = 0; x < SCREEN_WIDTH; x += sizeof(UINT8)){
      plot_text(base, x, y, font, text);
      text++;
    }
  }

  return 0;
}
