#include <osbind.h>

#include "ISR.H"


/* local vars */

volatile		unsigned char *const CTONTROL_ADDRESS	= 0xFFFC00;
volatile const 	unsigned char *const STATUS_ADDRESS		= 0xFFFC00;
volatile const 	unsigned char *const RDR_ADDRESS		= 0xFFFC02;
volatile		unsigned char *const MFP 				= 0xFFFA11; /* MULTI-FUNCTIONAL PERIPHERAL Interrupt in-service B */ 
volatile		unsigned char *const INTERRUPT_ENABLE	= 0xFFFA09; 

Vector	org_VBL;
Vector	org_IKBD;

UINT32 VBL_calls = 0; /* clock ticks */

bool render_mouse = TRUE;
bool mouse_enabled;


/* global vars */
UINT8 head = 0;
UINT8 tail = 0;
UINT8 IKBD_buffer[256];

int mouse_button = HEADER_PACKET; 
int mouse_status = 0;
int mouse_deltaXY[2];


void do_VBL_isr(){
	VBL_calls++;
}

void do_IKBD_isr(){
	UINT8 scancode = *RDR_ADDRESS;
	int read_loop = 0;

	if(mouse_status == FALSE){
		if(scancode >= HEADER_PACKET) 	/* is a mouse input */
		{
			mouse_button = scancode; 	/* 0th and 1st bit of header code is button states */
			mouse_status = TRUE;
		}
		else if( !(scancode & MAKECODE)){
			IKBD_buffer[tail++] = scancode; 
		}
	}
	else if(mouse_status == TRUE){
		while(read_loop < 2){
			mouse_deltaXY[read_loop] = scancode;
			scancode++;
		}	
	}
	*MFP = INTERRUPT_CLEAR; 
};

Vector install_vector(int num, Vector vector) {

	Vector	orig;
	Vector	*vectp = (Vector *)((long)num << 2);
	long	old_ssp = Super(0);

	orig	= *vectp;
	*vectp	= vector;

	Super(old_ssp);
	return orig;
};


void load_vectors(){
	mask_interrupts();
	
	org_VBL = install_vector(VBL_ISR, VBL_isr);
	org_IKBD = install_vector(IKBD_ISR, IKBD_isr);

	unmask_interrupts();
};

void restore_vector(){
	mask_interrupts();

	install_vector(VBL_ISR, org_VBL);
	install_vector(IKBD_ISR, org_IKBD);

	unmask_interrupts();
};

void mask_interrupts() {
	long old_ssp = Super(0);
	*INTERRUPT_ENABLE &= INTERRUPT_CLEAR;
	Super(old_ssp);
}

void unmask_interrupts() {
	long old_ssp = Super(0);
	*INTERRUPT_ENABLE |= INTERRUPT_SET;
	Super(old_ssp);
}

void init_cursor(UINT32 *base){

}

void update_cursor(UINT32 *base){
	
}