	GLOBAL	binsearch
binsearch:
	push	ebp
	mov	ebp,esp
	sub	esp,20
	mov	eax,0
	mov	[ebp-4],eax
	mov	eax,1
	mov	[ebp-16],eax
	mov	eax,[ebp+12]
	sub	eax,[ebp-16]
	mov	[ebp-8],eax
L0:
	mov	eax,[ebp-8]
	mov	[ebp-16],eax
	mov	eax,[ebp-4]
	cmp	eax,[ebp-16]
	setle	al
	movzx	eax,al
	cmp	eax,0
	je	L1
	mov	eax,2
	mov	[ebp-16],eax
	mov	eax,[ebp-8]
	mov	[ebp-20],eax
	mov	eax,[ebp-4]
	add	eax,[ebp-20]
	cdq	
	idiv	dword [ebp-16]
	mov	[ebp-12],eax
	EXTERN	v
	mov	eax,[ebp-12]
	push	eax
	call	v
	add	esp,4
	mov	[ebp-16],eax
	mov	eax,[ebp+8]
	cmp	eax,[ebp-16]
	setl	al
	movzx	eax,al
	cmp	eax,0
	je	L2
	mov	eax,1
	mov	[ebp-16],eax
	mov	eax,[ebp-12]
	sub	eax,[ebp-16]
	mov	[ebp-8],eax
	jmp	L3
L2:
	EXTERN	v
	mov	eax,[ebp-12]
	push	eax
	call	v
	add	esp,4
	mov	[ebp-16],eax
	mov	eax,[ebp+8]
	cmp	eax,[ebp-16]
	setg	al
	movzx	eax,al
	cmp	eax,0
	je	L4
	mov	eax,1
	mov	[ebp-16],eax
	mov	eax,[ebp-12]
	add	eax,[ebp-16]
	mov	[ebp-4],eax
	jmp	L5
L4:
	mov	eax,[ebp-12]
	jmp	Lret_binsearch
L5:
L3:
	jmp	L0
L1:
	mov	eax,1
	imul	eax,-1
	jmp	Lret_binsearch
Lret_binsearch:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	swap
swap:
	push	ebp
	mov	ebp,esp
	sub	esp,4
	EXTERN	v
	mov	eax,[ebp+8]
	push	eax
	call	v
	add	esp,4
	mov	[ebp-4],eax
	EXTERN	set_v
	EXTERN	v
	mov	eax,[ebp+12]
	push	eax
	call	v
	add	esp,4
	push	eax
	mov	eax,[ebp+8]
	push	eax
	call	set_v
	add	esp,8
	EXTERN	set_v
	mov	eax,[ebp-4]
	push	eax
	mov	eax,[ebp+12]
	push	eax
	call	set_v
	add	esp,8
Lret_swap:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	myqsort
myqsort:
	push	ebp
	mov	ebp,esp
	sub	esp,16
	mov	eax,[ebp+12]
	mov	[ebp-12],eax
	mov	eax,[ebp+8]
	cmp	eax,[ebp-12]
	setge	al
	movzx	eax,al
	cmp	eax,0
	je	L6
	mov	eax,0
	jmp	Lret_myqsort
L6:
	mov	eax,2
	mov	[ebp-12],eax
	mov	eax,[ebp+12]
	mov	[ebp-16],eax
	mov	eax,[ebp+8]
	add	eax,[ebp-16]
	cdq	
	idiv	dword [ebp-12]
	push	eax
	mov	eax,[ebp+8]
	push	eax
	call	swap
	add	esp,8
	mov	eax,[ebp+8]
	mov	[ebp-8],eax
	mov	eax,1
	mov	[ebp-12],eax
	mov	eax,[ebp+8]
	add	eax,[ebp-12]
	mov	[ebp-4],eax
L7:
	mov	eax,[ebp+12]
	mov	[ebp-12],eax
	mov	eax,[ebp-4]
	cmp	eax,[ebp-12]
	setle	al
	movzx	eax,al
	cmp	eax,0
	je	L8
	EXTERN	v
	mov	eax,[ebp+8]
	push	eax
	call	v
	add	esp,4
	mov	[ebp-12],eax
	EXTERN	v
	mov	eax,[ebp-4]
	push	eax
	call	v
	add	esp,4
	cmp	eax,[ebp-12]
	setl	al
	movzx	eax,al
	cmp	eax,0
	je	L9
	mov	eax,1
	mov	[ebp-12],eax
	mov	eax,[ebp-8]
	add	eax,[ebp-12]
	mov	[ebp-8],eax
	mov	eax,[ebp-4]
	push	eax
	mov	eax,[ebp-8]
	push	eax
	call	swap
	add	esp,8
L9:
	mov	eax,1
	mov	[ebp-12],eax
	mov	eax,[ebp-4]
	add	eax,[ebp-12]
	mov	[ebp-4],eax
	jmp	L7
L8:
	mov	eax,[ebp-8]
	push	eax
	mov	eax,[ebp+8]
	push	eax
	call	swap
	add	esp,8
	mov	eax,1
	mov	[ebp-12],eax
	mov	eax,[ebp-8]
	sub	eax,[ebp-12]
	push	eax
	mov	eax,[ebp+8]
	push	eax
	call	myqsort
	add	esp,8
	mov	eax,[ebp+12]
	push	eax
	mov	eax,1
	mov	[ebp-12],eax
	mov	eax,[ebp-8]
	add	eax,[ebp-12]
	push	eax
	call	myqsort
	add	esp,8
Lret_myqsort:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	main
main:
	push	ebp
	mov	ebp,esp
	sub	esp,0
	mov	eax,9
	push	eax
	mov	eax,0
	push	eax
	call	myqsort
	add	esp,8
	EXTERN	chk
	mov	eax,6
	push	eax
	mov	eax,10
	push	eax
	mov	eax,7
	push	eax
	call	binsearch
	add	esp,8
	push	eax
	call	chk
	add	esp,8
Lret_main:
	mov	esp,ebp
	pop	ebp
	ret	
