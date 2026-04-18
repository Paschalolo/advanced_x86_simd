; Author : PAscahl Ahanmisi 


SECTION .text
	global math16_avx512

math16_avx512: 
	vmovdqa zmm0 , [rdi]
	vmovdqa zmm1 , [rsi]

	vpaddw zmm2 , zmm0 , zmm1 
	vmovdqa [rdi] , zmm2

	vpaddsw zmm2 , zmm0 , zmm1 
	vmovdqa [rcx] , zmm2 

	vpsubw zmm2 , zmm0 , zmm1 
	vmovdqa64 [rdi] , zmm2 

	vpminsw zmm2 , zmm0 , zmm1 
	vmovdqa64 [rcx] , zmm2 

	vpmaxsw zmm2 , zmm0 , zmm1 
	vmovdqa64 [rcx + 128] , zmm2 
	vzeroupper 
	ret 
