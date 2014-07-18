	GLOBAL	fib
fib:
	push	ebp
	mov	ebp,esp
	sub	esp,8
	mov	dword [ebp-4],2
	mov	eax,[ebp+8]
	cmp	eax,[ebp-4]
	setl	al
	movzx	eax,al
	cmp	eax,0
	je	L0
	mov	eax,[ebp+8]
	jmp	Lret_fib
	jmp	L1
L0:
	mov	dword [ebp-4],2
	mov	eax,[ebp+8]
	sub	eax,[ebp-4]
	push	eax
	call	fib
	add	esp,4
	mov	[ebp-4],eax
	mov	dword [ebp-8],1
	mov	eax,[ebp+8]
	sub	eax,[ebp-8]
	push	eax
	call	fib
	add	esp,4
	add	eax,[ebp-4]
	jmp	Lret_fib
L1:
Lret_fib:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	main
main:
	push	ebp
	mov	ebp,esp
	sub	esp,0
	EXTERN	chk
	mov	eax,6765
	push	eax
	mov	eax,20
	push	eax
	call	fib
	add	esp,4
	push	eax
	call	chk
	add	esp,8
Lret_main:
	mov	esp,ebp
	pop	ebp
	ret	
