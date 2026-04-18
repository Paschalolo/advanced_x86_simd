
; Name : PAscahl Ahanmisi 
; extern "C" void MaskOpI64a_avx512(ZmmVal* c, uint8_t mask, const ZmmVal* a,
;   const ZmmVal* b);
;extern "C" void MaskOpI64b_avx512(ZmmVal* c, uint8_t mask, const ZmmVal* a,
;    const ZmmVal* b1, const ZmmVal* b2);
;extern "C" void MaskOpI64c_avx512(ZmmVal* c, const ZmmVal* a, int64_t x1,
 ;   int64_t x2)

; compare values 
CMP_EQ equ 0x00
CMP_LT equ 0x01 
CMP_LE equ 0x02 
CMP_FALSE equ 0x03 
CMP_NEG equ 0x04
CMP_NLT equ 0x05 
CMP_GE equ 0x06 
CMP_NLE equ 0x06
CMP_TRUE equ 0x07
;============================================
 SECTION .text 
 	global MaskOpI64a_avx512
MaskOpI64a_avx512:
	vmovdqa64 zmm1 , [rdi] 
	vmovdqa64 zmm1 , [rsi] 
	kmovb k1 , edx 

	vpaddq zmm2{k1}{z} , zmm0 , zmm1 
	vmovdqa64 [rdi] , zmm2 

	vpsubq zmm2{k1}{z} , zmm0 , zmm1 
	vmovdqa64 [rsi] , zmm0 

	vpmullq zmm2{k1}{z} , zmm0 , zmm1 
	vmovdqa64 [rcx], zmm2 

	vpsravq zmm2{k1}{z} , zmm0 , zmm1 
	vmovdqa64 [rdx] , zmm2 
	vzeroupper 
	ret
MaskOpI64b_avx512:
MaskOpI64c_avx512:
