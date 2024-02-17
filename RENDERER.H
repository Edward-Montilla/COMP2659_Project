#include "MODEL.H"
#include "TYPES.H"
#include "RASTER.H"

/* Render functions */
void render(const Model *model, UINT16 *base);
void render_reticle(const Reticle *ret, UINT16 *base);
void render_mallard(const Mallard *mal, UINT16 *base);