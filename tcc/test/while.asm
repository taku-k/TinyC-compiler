	GLOBAL	w
w:
	push	ebp
	mov	ebp,esp
	sub	esp,8
	mov	eax,0
	mov	[ebp-4],eax
L0:
	mov	eax,0
	mov	[ebp-8],eax
	mov	eax,[ebp+8]
	cmp	eax,[ebp-8]
	setg	al
	movzx	eax,al
	cmp	eax,0
	je	L1
	mov	eax,1
	mov	[ebp-8],eax
	mov	eax,[ebp-4]
	add	eax,[ebp-8]
	mov	[ebp-4],eax
	mov	eax,1
	mov	[ebp-8],eax
	mov	eax,[ebp+8]
	sub	eax,[ebp-8]
	mov	[ebp+8],eax
	jmp	L0
L1:
	mov	eax,[ebp-4]
	jmp	Lret_w
Lret_w:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	main
main:
	push	ebp
	mov	ebp,esp
	sub	esp,0
	EXTERN	chk
	mov	eax,10
	push	eax
	mov	eax,10
	push	eax
	call	w
	add	esp,4
	push	eax
	call	chk
	add	esp,8
Lret_main:
	mov	esp,ebp
	pop	ebp
	ret	
