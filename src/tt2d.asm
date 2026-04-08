; Author : Paschal Ahanmisi 
; Executablr 

;extern "C" void MulI32_a(int* prod1, long long* prod2, int a, int b);
; extern "C" int DivI32_a(int* quo, int* rem, int a, int b)

SECTION .text
	global MulI32_a
	global DivI32_a
MulI32_a:
	; value is in rax 
	mov eax , edx 
	imul ecx
	mov dword[rdi] , eax 
	shl rdx , 32
	or rax , rdx 
	mov qword[rsi] , rax 
	ret 

DivI32_a :
	mov eax , ecx 
	idiv rdx 
	mov dword[rdi] , eax 
	mov dword[rsi] , edx
