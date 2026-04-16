


SECTION .text 
	global _start 


_start : 
	vbroadcastsd ymm5 , [rdi] 
	vmulpd ymm4 , ymm5 , ymm0 

	vbroadcastsd ymm5 , [rdi+ disp * 8 ]
	vfmadd231pd ymm4 , ymm5 , ymm1 

	vbroadcastsd ymm5 , [rdi+ disp * 16 ]
	vfmadd231pd ymm4 , ymm5 , ymm2 

	vbroadcastsd ymm5 , [rdi+ disp * 32 ]
	vfmadd231pd ymm4 , ymm5 , ymm3

	vmovapd [rcx ] , ymm4


