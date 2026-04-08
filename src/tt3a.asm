 ;  Sumelements 
 ; Author : PAschal Ahanmisi 
 ; extern "C: int64_t sum_array(const int32_t* x , size_t n )
SECTION .text
	global sum_array 
sum_array:
	mov rcx , rsi
	mov rdx , 0
	mov rax , 0 
.sub_loop: 
	add eax , dword[rdi + rdx *4 ]
	inc rdx 
	loop
	ret 

 	
