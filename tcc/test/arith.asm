	GLOBAL	l
l:
	push	ebp
	mov	ebp,esp
	sub	esp,8
	mov	eax,[ebp+16]
	mov	[ebp-4],eax
	mov	eax,[ebp+12]
	mov	[ebp-8],eax
	mov	eax,[ebp+8]
	add	eax,[ebp-8]
	add	eax,[ebp-4]
	jmp	Lret_l
Lret_l:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	r
r:
	push	ebp
	mov	ebp,esp
	sub	esp,4
	mov	eax,3
	push	eax
	mov	eax,2
	push	eax
	mov	eax,1
	push	eax
	call	l
	add	esp,12
	mov	[ebp-4],eax
	mov	eax,[ebp+8]
	add	eax,[ebp-4]
	jmp	Lret_r
Lret_r:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	rsl1
rsl1:
	push	ebp
	mov	ebp,esp
	sub	esp,4
	mov	eax,3
	push	eax
	mov	eax,2
	push	eax
	mov	eax,1
	push	eax
	call	l
	add	esp,12
	mov	[ebp-4],eax
	mov	eax,[ebp+8]
	sub	eax,[ebp-4]
	jmp	Lret_rsl1
Lret_rsl1:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	rsl2
rsl2:
	push	ebp
	mov	ebp,esp
	sub	esp,4
	mov	eax,4
	push	eax
	call	r
	add	esp,4
	mov	[ebp-4],eax
	mov	eax,3
	push	eax
	mov	eax,2
	push	eax
	mov	eax,1
	push	eax
	call	l
	add	esp,12
	sub	eax,[ebp-4]
	jmp	Lret_rsl2
Lret_rsl2:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	arth
arth:
	push	ebp
	mov	ebp,esp
	sub	esp,12
	mov	eax,10
	mov	[ebp-4],eax
	mov	eax,[ebp+12]
	mov	[ebp-8],eax
	mov	eax,[ebp+8]
	sub	eax,[ebp-8]
	mov	[ebp+8],eax
	mov	eax,1
	mov	[ebp-8],eax
	mov	eax,[ebp+8]
	mov	[ebp-12],eax
	mov	eax,[ebp-4]
	sub	eax,[ebp-12]
	sub	eax,[ebp-8]
	mov	[ebp-4],eax
	mov	eax,[ebp-4]
	mov	[ebp-8],eax
	mov	eax,[ebp+8]
	add	eax,[ebp-8]
	jmp	Lret_arth
Lret_arth:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	main
main:
	push	ebp
	mov	ebp,esp
	sub	esp,0
	EXTERN	chk
	mov	eax,6
	push	eax
	mov	eax,3
	push	eax
	mov	eax,2
	push	eax
	mov	eax,1
	push	eax
	call	l
	add	esp,12
	push	eax
	call	chk
	add	esp,8
	EXTERN	chk
	mov	eax,16
	push	eax
	mov	eax,10
	push	eax
	call	r
	add	esp,4
	push	eax
	call	chk
	add	esp,8
	EXTERN	chk
	mov	eax,4
	push	eax
	mov	eax,10
	push	eax
	call	rsl1
	add	esp,4
	push	eax
	call	chk
	add	esp,8
	EXTERN	chk
	mov	eax,4
	imul	eax,-1
	push	eax
	call	rsl2
	add	esp,0
	push	eax
	call	chk
	add	esp,8
	EXTERN	chk
	mov	eax,9
	push	eax
	mov	eax,4
	push	eax
	mov	eax,2
	push	eax
	call	arth
	add	esp,8
	push	eax
	call	chk
	add	esp,8
Lret_main:
	mov	esp,ebp
	pop	ebp
	ret	
