

; Author : Paschal Ahanmisi
;extern "C" int64_t CalcResultI64_a(int8_t a, int16_t b, int32_t c, int64_t d,
 ;   int8_t e, int16_t f, int32_t g, int64_t h);
;extern "C" void CalcResultU64_a(uint8_t a, uint16_t b, uint32_t c, uint64_t d,
;    uint8_t e, uint16_t f, uint32_t g, uint64_t h, uint64_t* quo, uint64_t* rem);


SECTION .text 
	global CalcResultU64_a
CalcResultU64_a: 
	; caclulate a + b + c+ d
	mov rax , rcx 
	movzx rdi , dil
	movzx rsi , si
	add rdi , rsi 
	add rax , rdi 
	add rax , rdx
	; calculate e + f + g + h 
	movzx r8 , r8b
	movzx r9 , r9w
	add r8 , r9 
	push r10 
	push r11 
	mov r10d , dword[rsp + 8]
	mov r11d , dword[rsp + 16]
	add r10 , r11
	add r8 , r10 
	; (a+b+c_d ) / (e+f+g+h)
	xor rdx , rdx 
	div r8 
	mov rdi ,qword[rsp+24] 
	mov rsi , qword[rsp+ 32] 
	mov qword[rdi] , rax
	mov qword[rsi] , rdx
	pop r11 
	pop r10 
	ret 
