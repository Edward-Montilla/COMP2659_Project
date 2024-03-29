#include "MODEL.H"
#include "TYPES.H"
#include "RASTER.H"
#include "FONT.H"

/* Render functions */
void render(const Model *model, int *time_value, UINT16 *base);
void render_timer(int *time_value, UINT16 *base);
void render_reticle(const Reticle *ret, UINT16 *base);
void render_mallard(const Mallard *mal, UINT16 *base);

/* bitmaps */
extern const UINT16 reticle_bitmap[];
extern const UINT16 mallard_bitmap[];