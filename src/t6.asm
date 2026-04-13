; Name : PAschal Ahanmisi 
; ----------------------------------------------------------------
; int64_t SumIntegers_a(int8_t a, int16_t b, int32_t c, int64_t d,
;   int8_t e, int16_t f, int32_t g, int64_t h);
; ----------------------------------------------------------------
; extern "C" int64_t MulIntegers_a(int8_t a, int16_t b, int32_t c, int64_t d,
   ; int8_t e, int16_t f, int32_t g, int64_t h);
SECTION .text 
	global SumIntegers_a
	global MulIntegers_a
SumIntegers_a:
	ret
MulIntegers_a:
	movsx rdi , dil 
	movsx rsi , sil 
	movsx rdx , dl 
	movsx rcx , cl 
	movsx r8 , r8b
	movsx r9 , r9b 
	movzx r10 ,dword[rsp + 16]
	movzx r10 ,qword[rsp + 8]
	
