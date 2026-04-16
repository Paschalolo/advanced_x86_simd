
; Author : Pascahl Ahanmisi 
; Least squares 
;============================================================================
; extern "C" void CalcLeastSquares_avx2(double* m, double* b, const double* x<rdx>,
  ;  const double* y<rcx>, size_t n, double epsilon);
;============================================================================
%macro  REDUCEPD  4 ; 0->  destination  ymm 2 ->  xmm -1  xmmin-3  
	vextractf128 %1, %2 ,1 
	vaddpd  %1 , %3 , %1 
	vhaddpd %0 , %1 , %1 
%endmacro
SECTION .text
	global _start 

_start : 
	mov r12 , 0 
	mov r14 , r8 
	xor rax , rax 
	mov qword[rdi] , rax 
	mov qword[rsi] , rax
	vpxor ymm10, ymm10 , ymm10 ;  
	vpxor ymm11 , ymm11 , ymm11
	vpxor ymm12, ymm12 , ymm12
	vpxor ymm13, ymm13 , ymm13
	cmp r8 , 4 
	jl cacls 
	jz fin 
.loop:
	vmovapd ymm1, [rdx + r12 * 8 ]
	vmovapd ymm2, [rcx + r12 * 8 ]
	vaddpd ymm10 , ymm10 , ymm1 
	vaddpd ymm11 , ymm11 , ymm2
	
	; floating point multiply and add 
	vfmadd231pd ymm12 , ymm1 , ymm1 ; sumxx 
	vfmadd231pd ymm13 , ymm2 , ymm1	; sumxy 

	add r12 , 4
	sub r8 , 4 
	cmp  r8 , 4
	jae .loop	
	; loop for >= 8 
	
	REDUCEPD xmm10 , xmm1 , ymm10 , xmm10 ; contains sum_x
	REDUCEPD xmm11 , xmm1 , ymm11 , xmm11 ; contians sum_y 
	REDUCEPD xmm12 , xmm1 , ymm12 , xmm12 ; contains sumxx
	REDUCEPD xmm13 , xmm1 , ymm13 , xmm13; contains sumxy
	
	test r8 ,r8 
	jz cacls 
.sub_loop: 
	add r12 , 8 
	vmovsd xmm1 , [rdi + r12 * 8 ]
	vmovsd xmm2 , [rdi+ r12 * 8 ]
	vaddpd xmm10 , xmm10 , xmm1 
	vaddpd xmm11 , xmm11 , xmm2

	vfmadd231sd xmm12 , xmm1 , xmm1 ; sumxx 
	vfmadd231sd xmm13 , xmm2 , xmm1	; sumxy 
	sub r8 , 1 
	jnz .sub_loop
cacls :
	cvtsi2sd xmm4,r14 
	vmovq xmm5 ,xmm4 ; xmm5 is denom 
	vmulsd xmm0 , xmm5 , xmm12 
	vmulsd xmm1 , xmm10 , xmm10
	vsubsd xmm0 , xmm0 , xmm1 

	mov rax , 0x7fffffffffffffff
	vmovq xmm0, rax 
	vandpd xmm4 , xmm0 , xmm1
	vcomisd xmm3 , xmm2 , xmm4 
	vmovsd qword[rdi] , xmm3 
	vmulsd xmm1 , xmm12 , xmm11 
	vmulsd xmm2 , xmm13 , xmm10 
	vsubsd xmm6 , xmm2 , xmm1 
	vdivsd xmm3 ,xmm6 , xmm5 
	vmovsd qword[rsi] , xmm3 
fin : 
	vzeroupper
	ret 
