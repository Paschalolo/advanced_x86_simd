;	Author : PAscahl Ahanmisi 
;	Executable 
;
SECTION .text 
; --------------------------------------------------------
; extern "C" int AddSubI32_a(int a , int b , int c , int d);   
; --------------------------------------------------------
	global  AddSubI32_a
;function uses system v ABI 
AddSubI32_a: 
	; calculate (a+b) -(c+d) + 7 
	mov eax , 7 
	add edi , esi 
	add edx , ecx 
	sub edi , edx 
	add eax , edi 
	ret ; return function back to main 
	
