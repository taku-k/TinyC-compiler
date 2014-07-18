	GLOBAL	w
w:
	push	ebp
	mov	ebp,esp
	sub	esp,8
	mov	dword [ebp-4],0
L0:
	mov	dword [ebp-8],0
	mov	eax,[ebp+8]
	cmp	eax,[ebp-8]
	setg	al
	movzx	eax,al
	cmp	eax,0
	je	L1
	mov	dword [ebp-8],1
	mov	eax,[ebp-4]
	add	eax,[ebp-8]
	mov	[ebp-4],eax
	mov	dword [ebp-8],1
	mov	eax,[ebp+8]
	sub	eax,[ebp-8]
	mov	[ebp+8],eax
	jmp	L0
L1:
	mov	eax,[ebp-4]
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
