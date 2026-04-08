
;int int_shiftu32(unsigned int& a_shl , unsigned int& a_shr, unsigned int a , unsigned int count);

SECTION .text 
	global int_shiftu32

int_shiftu32:
	cmp ecx , 32 
	jae .Badcnt
	mov eax , edx 
	shl eax , cl 
	mov dword[rdi] , eax 
	shr edx , cl 
	mov dword[rsi] , edx
	mov eax , 1 
	ret 
.Badcnt:
	xor eax , eax
	ret 
