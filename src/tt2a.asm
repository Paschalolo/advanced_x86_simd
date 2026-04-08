; Author : Pascahl Ahanmisi 
SECTION .text 
	global BitOps32

; extern "C" unsigned int BitOps32(unsigned int a , unsigned int b , unsigned int c , unsigned int d );
 BitOps32: 
 	; calculate ~(((a&b) | c ) ^ d)
	mov eax , ecx 
	and edi , esi 
	or edi , edx 
	xor eax ,  edi
	not eax 
 	ret ; return to caller function 
