	.section	__TEXT,__text,regular,pure_instructions
	.globl	_i_to_b
	.align	4, 0x90
_i_to_b:                                ## @i_to_b
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
	sub	RSP, 32
	mov	DWORD PTR [RBP - 4], EDI
	mov	DWORD PTR [RBP - 8], ESI
	mov	ESI, DWORD PTR [RBP - 8]
	sub	ESI, 1
	mov	DWORD PTR [RBP - 12], ESI
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmp	DWORD PTR [RBP - 12], 0
	jl	LBB0_4
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	lea	RDI, QWORD PTR [RIP + L_.str]
	mov	EAX, 49
	mov	ECX, 48
	mov	EDX, 1
	mov	ESI, DWORD PTR [RBP - 4]
	mov	R8D, DWORD PTR [RBP - 12]
	mov	DWORD PTR [RBP - 20], ECX ## 4-byte Spill
	mov	ECX, R8D
                                        ## kill: CL<def> ECX<kill>
	shl	EDX, CL
	and	ESI, EDX
	cmp	ESI, 0
	setne	CL
	test	CL, CL
	mov	EDX, DWORD PTR [RBP - 20] ## 4-byte Reload
	cmove	EAX, EDX
	mov	CL, AL
	mov	BYTE PTR [RBP - 13], CL
	movsx	ESI, BYTE PTR [RBP - 13]
	mov	AL, 0
	call	_printf
	mov	DWORD PTR [RBP - 24], EAX ## 4-byte Spill
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	mov	EAX, DWORD PTR [RBP - 12]
	add	EAX, 4294967295
	mov	DWORD PTR [RBP - 12], EAX
	jmp	LBB0_1
LBB0_4:
	lea	RDI, QWORD PTR [RIP + L_.str1]
	mov	AL, 0
	call	_printf
	movabs	RDI, 0
	mov	DWORD PTR [RBP - 28], EAX ## 4-byte Spill
	mov	RAX, RDI
	add	RSP, 32
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
	sub	RSP, 48
	mov	EAX, 32
	mov	DWORD PTR [RBP - 4], 0
	mov	DWORD PTR [RBP - 8], EDI
	mov	QWORD PTR [RBP - 16], RSI
	mov	DWORD PTR [RBP - 20], -727711743
	mov	EDI, DWORD PTR [RBP - 20]
	mov	ESI, EAX
	call	_i_to_b
	mov	ESI, 8
	mov	EDI, DWORD PTR [RBP - 20]
	mov	CL, DIL
	mov	BYTE PTR [RBP - 21], CL
	movsx	EDI, BYTE PTR [RBP - 21]
	mov	QWORD PTR [RBP - 32], RAX ## 8-byte Spill
	call	_i_to_b
	lea	RDI, QWORD PTR [RIP + L_.str2]
	mov	ESI, DWORD PTR [RBP - 20]
	movsx	EDX, BYTE PTR [RBP - 21]
	mov	QWORD PTR [RBP - 40], RAX ## 8-byte Spill
	mov	AL, 0
	call	_printf
	mov	EDX, 0
	mov	DWORD PTR [RBP - 44], EAX ## 4-byte Spill
	mov	EAX, EDX
	add	RSP, 48
	pop	RBP
	ret
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	 "%c"

L_.str1:                                ## @.str1
	.asciz	 "\n"

L_.str2:                                ## @.str2
	.asciz	 "%d,%d\n"


.subsections_via_symbols
