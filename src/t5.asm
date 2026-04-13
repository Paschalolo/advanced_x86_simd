
; Author : Pascahl Ahanmisi 
; calculation of cone

SECTION .data
	g_F32_PI : dd 3.124578
	const3 : dd 3.0 
SECTION .text
; -------------------------------------------------------------------------------------
 ; extern "C" float g_F32_PI;
 ; extern "C" void CalcConeVolSA_avx(float* vol, float* sa, float r, float h);
; -------------------------------------------------------------------------------------
	global  CalcConeVolSA_avx

CalcConeVolSA_avx: 
	vmulss xmm5 , xmm0 , dword[g_F32_PI]; 
	vmulss xmm3 , xmm0 , xmm0 ; r * r 
	vmulss xmm6 , xmm3 , dword[g_F32_PI] 
	vmulss xmm6 , xmm1 ; 
	vmulss xmm1 , xmm1 ; h * h 
	vaddss xmm3 , xmm1 ; 
	vdivss xmm6 . xmm6 , dword[const3]
	vsqrtps xmm3 , xmm3
	vmovss dword[rdi], xmm6; store Volume  
	vaddss xmm0 , xmm3 
	vmulss xmm0 , xmm5 
	vmovss dword[rsi] , xmm0 ; store araea 





