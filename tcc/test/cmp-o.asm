	GLOBAL	cmp1
cmp1:
	push	ebp
	mov	ebp,esp
	sub	esp,8
	mov	eax,[ebp+12]
	mov	[ebp-4],eax
	mov	dword [ebp-8],1
	mov	eax,[ebp+8]
	add	eax,[ebp-8]
	cmp	eax,[ebp-4]
	setg	al
	movzx	eax,al
	cmp	eax,0
	je	L0
	mov	eax,1
	jmp	Lret_cmp1
	jmp	L1
L0:
	mov	eax,0
	jmp	Lret_cmp1
L1:
Lret_cmp1:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	cmp2
cmp2:
	push	ebp
	mov	ebp,esp
	sub	esp,4
	mov	dword [ebp-4],1
	mov	eax,[ebp+12]
	add	eax,[ebp-4]
	mov	[ebp-4],eax
	mov	eax,[ebp+8]
	cmp	eax,[ebp-4]
	setge	al
	movzx	eax,al
	cmp	eax,0
	je	L2
	mov	eax,1
	jmp	Lret_cmp2
	jmp	L3
L2:
	mov	eax,0
	jmp	Lret_cmp2
L3:
Lret_cmp2:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	cmp3
cmp3:
	push	ebp
	mov	ebp,esp
	sub	esp,4
	mov	dword [ebp-4],1
	mov	eax,[ebp+12]
	add	eax,[ebp-4]
	mov	[ebp-4],eax
	mov	eax,[ebp+8]
	cmp	eax,[ebp-4]
	setg	al
	movzx	eax,al
	cmp	eax,0
	je	L4
	mov	eax,1
	jmp	Lret_cmp3
	jmp	L5
L4:
	mov	eax,0
	jmp	Lret_cmp3
L5:
Lret_cmp3:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	main
main:
	push	ebp
	mov	ebp,esp
	sub	esp,0
	EXTERN	chk
	mov	eax,0
	push	eax
	mov	eax,3
	push	eax
	mov	eax,2
	push	eax
	call	cmp1
	add	esp,8
	push	eax
	call	chk
	add	esp,8
	EXTERN	chk
	mov	eax,1
	push	eax
	mov	eax,3
	push	eax
	mov	eax,4
	push	eax
	call	cmp2
	add	esp,8
	push	eax
	call	chk
	add	esp,8
	EXTERN	chk
	mov	eax,1
	push	eax
	mov	eax,2
	push	eax
	mov	eax,4
	push	eax
	call	cmp3
	add	esp,8
	push	eax
	call	chk
	add	esp,8
Lret_main:
	mov	esp,ebp
	pop	ebp
	ret	
