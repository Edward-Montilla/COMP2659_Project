#ifndef ISR_H
#define ISR_H

#include "MUSIC.H"
#include "RASTER.H"
#include "TYPES.H"


/* Trap Address */
#define VBL_ISR			28
#define IKBD_ISR		70

#define HEADER_PACKET	0xF8
#define MAKECODE 		0x80
#define INTERRUPT_CLEAR	0xBF
#define INTERRUPT_SET	0x40

/* mouse delta array constants */
#define DELTA_X 		0
#define DELTA_Y			1

#define ESC 			0x1B
#define W				0x77
#define A				0x61
#define S				0x73
#define D				0x64
#define SPC				0x20
typedef void (*Vector)(); 	/* a Vector is a function start address */

Vector install_vector(int num, Vector vector);

extern void VBL_isr();
extern void IKBD_isr();

void do_VBL_isr();
void do_IKBD_isr();

void load_vectors();
void restore_vectors();

void mask_interrupts();
void unmask_interrupts();

/* stage 10 additions */
void init_xursor();
void update_curor();

/* VBL ticks */
extern UINT32 VBL_calls;

extern bool render_mouse;

/* IKBD buffer queue */
extern UINT8 head; 
extern UINT8 tail; 
extern UINT8 IKBD_buffer[256]; 

extern bool mouse_status; /* 	FALSE == no mouse movement, TRUE == mouse movement */

extern int mouse_deltaXY[2]; /* index 0 == delta X , index 1 == delta Y */

extern int seconds; /* for testing purposes */
#endif