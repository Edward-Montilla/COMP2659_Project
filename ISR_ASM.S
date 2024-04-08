                                xdef                    _VBL_isr
                                xdef                    _IKBD_isr

                                xref                    _do_VBL_isr
                                xref                    _do_IKBD_isr

_VBL_isr:
                                movem.l                 d0-2/a0-2,-(sp)
                                jsr                             _do_VBL_isr       ; this routine is the ISR itself
                                movem.l                 (sp)+,d0-2/a0-2
                                rte
_IKBD_isr:
                                movem.l                 d0-2/a0-2,-(sp)
                                jsr                             _do_IKBD_isr      ; this routine is the ISR itself
                                movem.l                 (sp)+,d0-2/a0-2