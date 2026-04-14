; Auhtor : Paschal Ahanmisi 
; SIMD avx single precision packed 

SECTION .data 
	NSE equ 16 
SECTION .text 
; void CalcZ_avx(float* z, const float* x, const float* x, size_t n);

	global CalcZ_avx
; dat must be properly aligned at 32 bytes boundary
CalcZ_avx: 
	mov r8 , 0 
.loop:
	cmp rcx , NSE  
	jl smaller_fin 
	jz Done ; 
	vmovaps ymm0 , [rsi + r8 * 32  ] ; load x numbers 
	vmovaps ymm1, [rdx + r8 * 32 ] ; load y numbers 
	vmovaps ymm2 , [rsi + r8 * 64  ] ; load x1 numbers 
	vaddps ymm0 , ymm1 
	vmovaps ymm3, [rdx + r8 * 64 ] ; load y1 numbers 
	vaddps ymm2 , ymm3
	vmovntps [rdi + r8 * 32] , ymm0
	vmovntps [rdi + r8 * 64] , ymm0
	sub rcx , 16 
	add r8 , 2 
	jmp .loop
smaller_fin :
	test rcx , rcx 
	jz Done 
	vmovss xmm0 , dword[rsi + r8 * 4  ]
	vmovss  xmm1 , dword[rdx + r8 * 4 ]
	vaddss xmm0 , xmm0 , xmm1 
	vmovd eax , xmm0 
	movnti dword[rdi + r8 * 4] , eax
	dec rcx 
	inc r8 
	jmp smaller_fin

Done : 
	ret 

