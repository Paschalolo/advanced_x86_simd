; ===========================================================
;void AndU16_avx(XmmVal* c, const XmmVal* a, const XmmVal* b);
; ===========================================================
SECTION .text
AndU16_avx: 
	vmovdqa xmm0 , [rsi]
	vmovdqa xmm1 , [rdx]
	vpand xmm0 , xmm1 
	vmovdqa [rdi] , xmm0
	ret 
