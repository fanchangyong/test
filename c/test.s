	.section	__TEXT,__text,regular,pure_instructions
	.globl	_f
	.align	4, 0x90
_f:                                     ## @f
	.cfi_startproc
## BB#0:
	push	RBP
Ltmp2:
	.cfi_def_cfa_offset 16
Ltmp3:
	.cfi_offset rbp, -16
	mov	RBP, RSP
Ltmp4:
	.cfi_def_cfa_register rbp
	mov	DWORD PTR [RBP - 4], EDI
	pop	RBP
	ret
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	push	RBP
Ltmp7:
	.cfi_def_cfa_offset 16
Ltmp8:
	.cfi_offset rbp, -16
	mov	RBP, RSP
Ltmp9:
	.cfi_def_cfa_register rbp
	sub	RSP, 16
	mov	EAX, 5
	mov	DWORD PTR [RBP - 4], 0
	mov	DWORD PTR [RBP - 8], EDI
	mov	QWORD PTR [RBP - 16], RSI
	mov	EDI, EAX
	call	_f
	mov	EAX, 0
	add	RSP, 16
	pop	RBP
	ret
	.cfi_endproc


.subsections_via_symbols
