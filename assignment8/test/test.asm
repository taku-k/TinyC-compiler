	GLOBAL	foo
foo	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	eax, 4
	mov	[ebp-4], eax
	mov	eax, 3
	mov	[ebp-8], eax
	mov	eax, [ebp+8]
	cmp	eax, [ebp-8]
	setne	al
	movzx	eax, al
	cmp	eax, 0
	je	L0
	mov	eax, [ebp+8]
	mov	[ebp-8], eax
	mov	eax, [ebp-4]
	imul	eax, [ebp-8]
	mov	[ebp-4], eax
	jmp	L1
	mov	eax, [ebp+8]
	mov	[ebp-4], eax
L0:
L1:
	mov	eax, [ebp-4]
	jmp	Lret
Lret	mov	esp, ebp
	pop	ebp
	ret
