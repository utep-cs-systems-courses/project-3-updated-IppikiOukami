		.arch msp430g2553
		.p2align 2
		.text
jt:
	.word end
	.word case1
	.word case2
	.word case3
	.word case4

	.extern super_state	;state indicator
	.extern leds_changed	;led indicator

	.global state_advance
state_advance:
	sub #2, r1 		;move pointer
	mov #0, 0(r1)		;super_state = 0
	cmp.b #5, &super_state	;jmp if C flag == 1
	jhs end			;^^^^^^^^^^^^^^^^^^
	mov.b &super_state, r12
	add.b r12, r12		;double r12
	mov jt(r12), r0

case1:	call #state1		;changed = state1
	mov.b r12, 0(r1)	;move value of super_state into 0(r1)
	jmp end
case2:	call #state2
	mov.b r12, 0(r1)
	jmp end
case3:	call #state3
	mov.b r12, 0(r1)
	jmp end
case4:	call #state4
	mov.b r12, 0(r1)
	jmp end
end:
	mov.b 0(r1), &leds_changed ;revert led against value of 0(r1)
	add #2, r1		;reset pointer
	call #led_modify
	pop r0			
