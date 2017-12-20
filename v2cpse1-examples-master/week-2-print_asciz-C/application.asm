   .cpu cortex-m0
   .text
   .align 2
   .global application

application:
	bl print_asciz
	mov pc, lr
