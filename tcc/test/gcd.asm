	GLOBAL	gcd
gcd:
	push	ebp
	mov	ebp,esp
	sub	esp,4
	mov	eax,[ebp+12]
	mov	[ebp-4],eax
	mov	eax,[ebp+8]
	cmp	eax,[ebp-4]
	sete	al
	movzx	eax,al
	cmp	eax,0
	je	L0
	mov	eax,[ebp+8]
	jmp	Lret_gcd
	jmp	L1
L0:
	mov	eax,[ebp+12]
	mov	[ebp-4],eax
	mov	eax,[ebp+8]
	cmp	eax,[ebp-4]
	setg	al
	movzx	eax,al
	cmp	eax,0
	je	L2
	mov	eax,[ebp+12]
	push	eax
	mov	eax,[ebp+12]
	mov	[ebp-4],eax
	mov	eax,[ebp+8]
	sub	eax,[ebp-4]
	push	eax
	call	gcd
	add	esp,8
	jmp	Lret_gcd
	jmp	L3
L2:
	mov	eax,[ebp+8]
	mov	[ebp-4],eax
	mov	eax,[ebp+12]
	sub	eax,[ebp-4]
	push	eax
	mov	eax,[ebp+8]
	push	eax
	call	gcd
	add	esp,8
	jmp	Lret_gcd
L3:
L1:
Lret_gcd:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	main
main:
	push	ebp
	mov	ebp,esp
	sub	esp,0
	EXTERN	chk
	mov	eax,63
	push	eax
	mov	eax,189
	push	eax
	mov	eax,315
	push	eax
	call	gcd
	add	esp,8
	push	eax
	call	chk
	add	esp,8
Lret_main:
	mov	esp,ebp
	pop	ebp
	ret	
