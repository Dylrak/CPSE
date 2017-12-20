   .cpu cortex-m0
   .text
   .align 2
   .global application

application:
	push { r0, lr }
	bl print_asciz
	pop { r0, pc }
