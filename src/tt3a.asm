 ;  Sumelements 
 ; Author : PAschal Ahanmisi 
 ; extern "C: int64_t sum_array(const int32_t* x , size_t n )
SECTION .text
	global calcu_array
; void calcu_array (int64_t* c , const int64_t* a , const int64_t* b , size_t n );
; c[i] = (a[i] * 25 ) / (b[i] + 10)
calcu_array:
	; rcx cpontains loop count 
	mov r8 , 0 
	mov r10 , rdi 
	mov rdi ,  rdx 
.sub_loop: 
	imul r9 , qword[rsi + r8 * 8 ], 25 
	mov rax , qword[rdi + r8 * 8] 
	add rax , 10 
	idiv r9
	mov qword[r10 + r8 * 8],rax
	inc r8
	sub rcx , 1 
	jnz .sub_loop
	xor rax , rax 
	ret 
