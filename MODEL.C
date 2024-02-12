#include "MODEL.H"

void move_reticle(Reticle *reticle) {
  reticle->x += reticle->dx;
  reticle->y += reticle->dy;
};

void move_mallard(Mallard *mallard) {
  if (mallard->is_dead)
    return;

  mallard->x += mallard->dx;
  mallard->y += mallard->dy;
};

bool is_hit(Reticle *reticle, Mallard *mallard) {
  bool hit = false;
  if (reticle->x == mallard->x && reticle->y == mallard->y) {
    hit = true;
  }
  return hit;
};
