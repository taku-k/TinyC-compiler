	GLOBAL	ack
ack:
	push	ebp
	mov	ebp,esp
	sub	esp,4
	mov	dword [ebp-4],0
	mov	eax,[ebp+8]
	cmp	eax,[ebp-4]
	sete	al
	movzx	eax,al
	cmp	eax,0
	je	L0
	mov	dword [ebp-4],1
	mov	eax,[ebp+12]
	add	eax,[ebp-4]
	jmp	Lret_ack
L0:
	mov	dword [ebp-4],0
	mov	eax,[ebp+12]
	cmp	eax,[ebp-4]
	sete	al
	movzx	eax,al
	cmp	eax,0
	je	L1
	mov	eax,1
	push	eax
	mov	dword [ebp-4],1
	mov	eax,[ebp+8]
	sub	eax,[ebp-4]
	push	eax
	call	ack
	add	esp,8
	jmp	Lret_ack
L1:
	mov	dword [ebp-4],1
	mov	eax,[ebp+12]
	sub	eax,[ebp-4]
	push	eax
	mov	eax,[ebp+8]
	push	eax
	call	ack
	add	esp,8
	push	eax
	mov	dword [ebp-4],1
	mov	eax,[ebp+8]
	sub	eax,[ebp-4]
	push	eax
	call	ack
	add	esp,8
Lret_ack:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	main
main:
	push	ebp
	mov	ebp,esp
	sub	esp,0
	EXTERN	chk
	mov	eax,29
	push	eax
	mov	eax,2
	push	eax
	mov	eax,3
	push	eax
	call	ack
	add	esp,8
	push	eax
	call	chk
	add	esp,8
	EXTERN	chk
	mov	eax,61
	push	eax
	mov	eax,3
	push	eax
	mov	eax,3
	push	eax
	call	ack
	add	esp,8
	push	eax
	call	chk
	add	esp,8
	EXTERN	chk
	mov	eax,125
	push	eax
	mov	eax,4
	push	eax
	mov	eax,3
	push	eax
	call	ack
	add	esp,8
	push	eax
	call	chk
	add	esp,8
Lret_main:
	mov	esp,ebp
	pop	ebp
	ret	
