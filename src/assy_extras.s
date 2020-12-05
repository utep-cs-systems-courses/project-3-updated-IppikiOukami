	.text
	.global cmp_assembly
cmp_assembly:
	cmp #0, r12
	jge triggered
not_triggered:
	mov #0, r12
	jmp end
triggered:
	mov #1, r12
end:
	pop r0
