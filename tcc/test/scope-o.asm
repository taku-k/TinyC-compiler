	GLOBAL	logi1
logi1:
	push	ebp
	mov	ebp,esp
	sub	esp,16
	mov	dword [ebp-4],1
	mov	dword [ebp-8],0
	mov	dword [ebp-12],1
	mov	eax,[ebp+12]
	add	eax,[ebp-12]
	mov	[ebp-12],eax
	mov	eax,[ebp+8]
	cmp	eax,[ebp-12]
	setl	al
	movzx	eax,al
	cmp	eax,0
	je	L3
	mov	eax,[ebp+16]
	mov	[ebp-12],eax
	mov	dword [ebp-16],1
	mov	eax,[ebp+12]
	add	eax,[ebp-16]
	cmp	eax,[ebp-12]
	setl	al
	movzx	eax,al
	cmp	eax,0
	je	L3
	mov	dword [ebp-8],1
L3:
	mov	eax,[ebp-8]
	cmp	eax,0
	je	L2
	mov	dword [ebp-12],0
	mov	eax,[ebp+12]
	cmp	eax,[ebp-12]
	sete	al
	movzx	eax,al
	cmp	eax,0
	je	L2
	mov	dword [ebp-4],0
L2:
	mov	eax,[ebp-4]
	cmp	eax,0
	je	L0
	mov	eax,1
	jmp	Lret_logi1
	jmp	L1
L0:
	mov	eax,0
	jmp	Lret_logi1
L1:
Lret_logi1:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	logi2
logi2:
	push	ebp
	mov	ebp,esp
	sub	esp,12
	mov	dword [ebp-4],1
	mov	dword [ebp-8],0
	mov	eax,[ebp+12]
	mov	[ebp-12],eax
	mov	eax,[ebp+8]
	cmp	eax,[ebp-12]
	setl	al
	movzx	eax,al
	cmp	eax,0
	je	L7
	mov	eax,[ebp+16]
	mov	[ebp-12],eax
	mov	eax,[ebp+12]
	cmp	eax,[ebp-12]
	setl	al
	movzx	eax,al
	cmp	eax,0
	je	L7
	mov	dword [ebp-8],1
L7:
	mov	eax,[ebp-8]
	cmp	eax,0
	je	L6
	mov	eax,[ebp+20]
	cmp	eax,0
	je	L6
	mov	dword [ebp-4],0
L6:
	mov	eax,[ebp-4]
	cmp	eax,0
	je	L4
	mov	eax,1
	jmp	Lret_logi2
	jmp	L5
L4:
	mov	eax,0
	jmp	Lret_logi2
L5:
Lret_logi2:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	logi3
logi3:
	push	ebp
	mov	ebp,esp
	sub	esp,16
	mov	dword [ebp-4],0
	mov	dword [ebp-8],3
	mov	eax,[ebp+12]
	cmp	eax,[ebp-8]
	sete	al
	movzx	eax,al
	cmp	eax,0
	je	L10
	mov	eax,[ebp+8]
	mov	[ebp-8],eax
	mov	eax,[ebp+12]
	sub	eax,[ebp-8]
	cmp	eax,0
	je	L10
	mov	dword [ebp-4],1
L10:
	mov	eax,[ebp-4]
	cmp	eax,0
	je	L8
	mov	dword [ebp-8],1
	mov	dword [ebp-12],0
	mov	eax,[ebp+8]
	cmp	eax,[ebp-12]
	sete	al
	movzx	eax,al
	cmp	eax,0
	je	L13
	mov	eax,[ebp+12]
	mov	[ebp-12],eax
	mov	eax,[ebp+8]
	imul	eax,[ebp-12]
	mov	[ebp-12],eax
	mov	eax,[ebp+12]
	mov	[ebp-16],eax
	mov	eax,[ebp+8]
	add	eax,[ebp-16]
	cmp	eax,[ebp-12]
	setl	al
	movzx	eax,al
	cmp	eax,0
	je	L13
	mov	dword [ebp-8],0
L13:
	mov	eax,[ebp-8]
	cmp	eax,0
	je	L11
	mov	eax,1
	jmp	Lret_logi3
	jmp	L12
L11:
	mov	eax,0
	jmp	Lret_logi3
L12:
	jmp	L9
L8:
	mov	eax,0
	jmp	Lret_logi3
L9:
Lret_logi3:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	main
main:
	push	ebp
	mov	ebp,esp
	sub	esp,0
	EXTERN	chk
	mov	eax,1
	push	eax
	mov	eax,3
	push	eax
	mov	eax,4
	push	eax
	mov	eax,2
	push	eax
	mov	eax,1
	push	eax
	call	logi1
	add	esp,16
	push	eax
	call	chk
	add	esp,8
	EXTERN	chk
	mov	eax,1
	push	eax
	mov	eax,0
	push	eax
	mov	eax,3
	push	eax
	mov	eax,2
	push	eax
	mov	eax,1
	push	eax
	call	logi2
	add	esp,16
	push	eax
	call	chk
	add	esp,8
	EXTERN	chk
	mov	eax,1
	push	eax
	mov	eax,3
	push	eax
	mov	eax,2
	push	eax
	call	logi3
	add	esp,8
	push	eax
	call	chk
	add	esp,8
Lret_main:
	mov	esp,ebp
	pop	ebp
	ret	
