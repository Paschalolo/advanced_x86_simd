
; Name : Ahanmisi Pascahl 

;extern "C" void MulI16_avx(XmmVal c[2], const XmmVal* a, const XmmVal* b);
;extern "C" void MulI32a_avx(XmmVal* c, const XmmVal* a, const XmmVal* b);
;extern "C" void MulI32b_avx(XmmVal c[2], const XmmVal* a, const XmmVal* b);


SECTION .text 
	global MulI16_avx
	global MulI32a_avx
	global MulI32b_avx


MulI16_avx:
	vmovdqa xmm0 , [rsi]
	vmovdqa xmm1 , [rdx]
	vpmullw xmm2 , xmm1 
	vmovdqa [rdi] , xmm0 
	ret 
MulI32a_avx:
MulI32b_avx:

