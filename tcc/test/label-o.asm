	GLOBAL	lab
lab:
	push	ebp
	mov	ebp,esp
	sub	esp,8
	mov	dword [ebp-4],1
	mov	dword [ebp-8],0
	mov	eax,[ebp-4]
	cmp	eax,0
	je	L0
	mov	eax,[ebp-8]
	cmp	eax,0
	je	L1
	mov	eax,0
	jmp	Lret_lab
	jmp	L2
L1:
	mov	eax,2
	jmp	Lret_lab
L2:
L0:
Lret_lab:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	main
main:
	push	ebp
	mov	ebp,esp
	sub	esp,0
	EXTERN	chk
	mov	eax,2
	push	eax
	call	lab
	add	esp,0
	push	eax
	call	chk
	add	esp,8
Lret_main:
	mov	esp,ebp
	pop	ebp
	ret	
