/*******************************************************************************
 * STUDENT: Jaunie Williams, Edward Montilla                                   *
 *                                                                             *
 * COURSE: COMP2659 - COMPUTING MACHINERY II                                   *
 *                                                                             *
 * PROFESSOR: Marc Schroeder								                   *
 * 							                                                   *
 * PURPOSE: Handles all rendering and large bitmap handling.                   *
 *                                                                             *
 *******************************************************************************/

#include "MODEL.H"
#include "TYPES.H"
#include "RASTER.H"
#include "FONT.H"

/* Render functions */
void render(const Model *model, int *time_value, UINT16 *base);
void render_timer(int *time_value, UINT16 *base);
void render_reticle(const Reticle *ret, UINT16 *base);
void render_mallard(const Mallard *mal, UINT16 *base);