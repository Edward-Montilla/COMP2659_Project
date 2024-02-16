#define bool int
#define FALSE 0
#define TRUE 1

typedef struct {
  /* position variables */
  unsigned int x, y;
  /* size variables*/
  const int width, height;
  /* displacement variables */
  int dx, dy;
} Reticle;

typedef struct {
  /* position variables */
  unsigned int x, y;
  /* size variables*/
  const int width, height;
  /* displacement variables */
  int dx, dy;
  /* out of play variable */
  bool is_dead;
} Mallard;

/* A structure for all models */
typedef struct {
  Reticle reticle;
  Mallard mallards[2];
} Model;

/* Prototypes */
void move_reticle(Reticle *reticle);
void move_mallard(Mallard *mallard);
bool is_hit(Reticle *reticle, Mallard *mallard);
