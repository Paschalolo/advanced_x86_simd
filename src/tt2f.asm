
; extern "C" int g_NumPrimes_a ; 
; extern "C" int g_SumPrimes_a ;
SECTION .data 
	PrimeNumber : dd 1000 
SECTION .bss
	align 4 
	g_NumPrimes_a : resd 1 
	align 4
	g_SumPrimes_a : resd 1 
; int Mem_addressing(int32_t , int32_t* , int32_t* , int32_t*, int32_t*);

SECTION .text 
	global Mem_addressing

Mem_addressing: 
	cmp edi , -1 
	jle invalidIndex 
	cmp edi , dword[g_NumPrimes_a] 
	jge  invalidIndex 
	; Initializes 
	movsxd rdi , edi 
	lea r11 , [PrimeNumber] ; r11 contans address of r11 
	; Memory adddresing - base registers 
	mov eax , dword[r11 + rdi*4 ]; 

invalidIndex:
	ret 	
