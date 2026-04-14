; Author : Pascahl Ahanmisis 

SECTION .text


 ; ---------------------------------------------------------------
; 	extern "C" void AddI16_avx(XmmVal* c1, XmmVal* c2, const XmmVal* a,
  ;  const XmmVal* b);
 ; ---------------------------------------------------------------
 	global AddI16_avx 
 	global SubI16_avx
 AddI16_avx:
 	vmovdqa xmm1 , [rdx]
 	vmovdqa xmm0 , [rcx]
 	vpaddw xmm0 , xmm0 , xmm1 
 	vpaddsw xmm3 , xmm0 , xmm1 
	vmovdqa [rdi] , xmm0 
	vmovdqa [rsi] , xmm3 
	ret 
 ; ---------------------------------------------------------------
;extern "C" void SubI16_avx(XmmVal* c1, XmmVal* c2, const XmmVal* a,
 ;   const XmmVal* b);
 ; ---------------------------------------------------------------
 SubI16_avx:
 	vmovdqa xmm1 , [rdx]
 	vmovdqa xmm0 , [rcx]
 	vpsubw xmm0 , xmm0 , xmm1 
 	vpsubsw xmm3 , xmm0 , xmm1 
	vmovdqa [rdi] , xmm0 
	vmovdqa [rsi] , xmm3 
	ret 
