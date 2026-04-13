
; Author : Paschal Ahanmisi 
; C = (F - 32) * 5/9 
; F = (C * 9/5) + 32

SECTION .data 
	f32_scaleFtoC dd 0.555556 ; 
	f32_scaleCtoF dd 1.8 
	f32_32_po dd 32.0 


SECTION .text 
	; --------------------------------------------------------------------------------------
	; float ConvertFtoC_avx(float deg_f)
	; --------------------------------------------------------------------------------------

	global ConvertFtoC_avx
	global ConvertCtoF_avx

ConvertFtoC_avx: 
	vmovss xmm0 , dword[f32_scaleFtoC] ; 
	vsubss xmm2 , xmm0 , xmm1 

	vmovss xmm1 , dword[f32_32_po]
	vmulss xmm0 , xmm2 ,xmm1
	ret;
	; --------------------------------------------------------------------------------------
	; float ConvertFtoC_avx(float deg_f)
	; --------------------------------------------------------------------------------------

ConvertCtoF_avx:
	vmulss xmm0 , xmm0 , dword[f32_scaleCtoF] ; 
	vaddss xmm0 , xmm0 , dword[f32_32_po]
	ret
