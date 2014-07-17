	COMMON	x	4
	COMMON	y	4
	GLOBAL	f
f:
	push	ebp
	mov	ebp,esp
	sub	esp,4
	mov	eax,3
	mov	[y],eax
	mov	eax,[y]
	mov	[ebp-4],eax
	mov	eax,[ebp+8]
	add	eax,[ebp-4]
	jmp	Lret_f
Lret_f:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	g
g:
	push	ebp
	mov	ebp,esp
	sub	esp,4
	mov	eax,[ebp+8]
	mov	[ebp-4],eax
	mov	eax,[x]
	add	eax,[ebp-4]
	jmp	Lret_g
Lret_g:
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	main
main:
	push	ebp
	mov	ebp,esp
	sub	esp,0
	mov	eax,4
	mov	[x],eax
	EXTERN	chk
	mov	eax,5
	push	eax
	mov	eax,2
	push	eax
	call	f
	add	esp,4
	push	eax
	call	chk
	add	esp,8
	EXTERN	chk
	mov	eax,7
	push	eax
	mov	eax,3
	push	eax
	call	g
	add	esp,4
	push	eax
	call	chk
	add	esp,8
Lret_main:
	mov	esp,ebp
	pop	ebp
	ret	
