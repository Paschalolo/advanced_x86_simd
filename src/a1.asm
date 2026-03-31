

; Author : Pascahl Ahamisii 

; Function of A1 using raw assembly 

;-------------------------------------------------------------------------------------------
;			a1.asm
;-------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------
; extern "C" void calcx_avx(float* z , const float* x , const float* y , size_t n ) 	
;-------------------------------------------------------------------------------------------
SECTION .data 
	NSE equ 8 
SECTION .text 
	global calcx_avx2 

; fucntion must be aligned on a 16 | 64 byte  byte boundary 
calcx_avx2: 
	xor rax , rax ; i = 0
	; rcx -> n 

.loop : 
	mov r8 , rcx 
	sub r8 , rax 
	cmp r8  , NSE 
	jl .scalr_values ; jump to finish scalar function 
	add rax , NSE 
	vmovaps ymm0 , [rsi] ; mov x -> ymm0 
	vmovaps ymm1 , [rdx] ; mov y -> ymm1
	vaddps ymm1 , ymm1 , ymm0; add x[i...8 values] + y[i...]
	vmovntpd [rdi] , ymm1 ; mov and aviod any caching 
	jmp .loop ; jump back to loop 
; scalar function handling 
.scalr_values : 
	cmp rax , rcx 
	jae .Done 
	vmovss xmm0 , dword[rsi]
	vaddss xmm0 , xmm0 , dword[rdx]
	vmovss dword[rdi], xmm0; mov back to z
	inc rax 
	jmp .scalr_values

.Done : 
	vzeroupper ; zeros the upper bits of the ymm and zmmm registers 
	ret 
	
	
	



