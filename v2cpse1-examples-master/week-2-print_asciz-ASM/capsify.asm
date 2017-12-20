   .cpu cortex-m0
   .text
   .align 1
   .global capsify

capsify:
	push { r1 - r6 }
	mov r1, #'a'
	mov r2, #'z'
	mov r3, #'A'
	mov r4, #'Z'
	mov r5, #32
lowercase:
	mov r6, r0
	cmp r0, r1
	blt uppercase
	mov r0, r6
	cmp r0, r2
	bgt done
	mov r0, r6
	sub r0, r0, r5
	b done
uppercase:
	mov r0, r6
	cmp r0, r3
	blt done
	mov r0, r6
	cmp r0, r4
	bgt done
	mov r0, r6
	add r0, r0, r5
	b done
done:
	pop { r1-r6 }
	mov pc, lr
