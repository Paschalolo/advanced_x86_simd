; Author : Pascahl Ahanmisi

SECTION .text 
	 ; long long AddSubI64a_a(long long a, long long b, long long c, long long d);
	 global AddSubI64a_a
	 global AddSubI64a_b
	 ; Calculate (a + b) - (c + d) + 7
	 ; Calculate (a + b) - (c + d) + 12345678900
	 AddSubI64a_a: 
	 	mov rax , 7 
		add rdi , rsi 
		add rdx , rcx 
		sub rdi , rdx 
		add rax , rdi 
		ret ; return to caller function 
	 AddSubI64a_b :
	  	mov rax , 0x2DFDC1C34
		add rdi , rsi 
		add rdx , rcx 
		sub rdi , rdx 
		add rax , rdi 
		ret ; return to caller function 
