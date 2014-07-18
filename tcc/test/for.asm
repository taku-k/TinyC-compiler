	GLOBAL	fortest
fortest:
	push	ebp
	mov	ebp,esp
	sub	esp,12
	mov	eax,0
	mov	[ebp-8],eax
	mov	eax,0
	mov	[ebp-4],eax
L0:
	mov	eax,[ebp+8]
	mov	[ebp-12],eax
	mov	eax,[ebp-4]
	cmp	eax,[ebp-12]
	setl	al
	movzx	eax,al
	cmp	eax,0
	je	L1
	mov	eax,2
	mov	[ebp-12],eax
	mov	eax,[ebp-8]
	add	eax,[ebp-12]
	mov	[ebp-8],eax
	mov	eax,1
	add	[ebp-4],eax
	jmp	L0
L1:
	mov	eax,[ebp-8]
	jmp	Lret_fortest
Lret_fortest:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	main
main:
	push	ebp
	mov	ebp,esp
	sub	esp,0
	EXTERN	chk
	mov	eax,20
	push	eax
	mov	eax,10
	push	eax
	call	fortest
	add	esp,4
	push	eax
	call	chk
	add	esp,8
Lret_main:
	mov	esp,ebp
	pop	ebp
	ret	
