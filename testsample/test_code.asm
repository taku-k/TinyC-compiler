	BITS    32
    GLOBAL	_test_code
    SECTION .text
_test_code:
	push	ebp
	mov	ebp,esp
	sub	esp,20
	mov	eax,1
	mov	[ebp-4],eax
	mov	eax,1
	mov	[ebp-12],eax
	mov	eax,2
	mov	[ebp-16],eax
	mov	eax,4
	mov	[ebp-20],eax
	mov	eax,8
	or	eax,[ebp-20]
	or	eax,[ebp-16]
	or	eax,[ebp-12]
	mov	[ebp-8],eax
	mov	eax,15
	mov	[ebp-12],eax
	mov	eax,[ebp-8]
	cmp	eax,[ebp-12]
	setne	al
	movzx	eax,al
	cmp	eax,0
	je	L0
	mov	eax,0
	mov	[ebp-4],eax
L0:
	mov	eax,[ebp-4]
	mov	esp,ebp
	pop	ebp
	ret	
	GLOBAL	_main
    EXTERN  _chk
_main:
	push	ebp
	mov	ebp,esp
	sub	esp,0
	EXTERN	chk
	mov	eax,15
	push	eax
	call	_test_code
	add	esp,0
	push	eax
	call	_chk
	add	esp,8
Lret_main:
	mov	esp,ebp
	pop	ebp
	ret	
