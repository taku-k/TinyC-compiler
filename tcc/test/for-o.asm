	GLOBAL	fortest
fortest:
	push	ebp
	mov	ebp,esp
	sub	esp,12
	mov	dword [ebp-8],0
	mov	dword [ebp-4],0
L0:
	mov	eax,[ebp+8]
	mov	[ebp-12],eax
	mov	eax,[ebp-4]
	cmp	eax,[ebp-12]
	setl	al
	movzx	eax,al
	cmp	eax,0
	je	L1
	mov	dword [ebp-12],2
	mov	eax,[ebp-8]
	add	eax,[ebp-12]
	mov	[ebp-8],eax
	add	dword [ebp-4],1
	jmp	L0
L1:
	mov	eax,[ebp-8]
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
