; Author : pAscahl Ahanmisi 

SECTION .data 
	 g_F64_PI : dq 3.14 
SECTION .text
;extern "C" void CalcSphereVolSA_avx(double* vol, double* sa, double r);
; extern "C" double g_F64_PI;
	global CalcSphereVolSA_avx 

CalcSphereVolSA_avx:
	mov rax , 0x4 
	mov rcx , 0x3
	vmovq xmm5 , rax 
	vmovq xmm6 , rcx
	vmulss xmm0 , xmm0 , xmm0 ; r * r 
	vmulss xmm1, xmm0 ,  qword[g_F64_PI] ; r *r * pi 
	vmulss xmm5 , xmm5 , xmm1 
	vmulss xmm0 , xmm5 , xmm0 
	vmovq qword[rsi] , xmm5 

	vdivss xmm6 , xmm0, xmm6  
	vmovq qword[rdi] , smm6 
	; next function 
	ret 
