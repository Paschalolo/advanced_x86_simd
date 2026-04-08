
#include <cstdio>
extern "C" unsigned int BitOps32(unsigned int a , unsigned int b , unsigned int c , unsigned int d );
unsigned int BitOps32_cpp(unsigned int a , unsigned int b , unsigned int c , unsigned int d );

void result_print(unsigned int r1 , unsigned int r2){
	std::printf("%d %d", r1, r2);	
}




unsigned int BitOps32_cpp(unsigned int a , unsigned int b , unsigned int c , unsigned int d ){
	// calculate ~(((a&b) | c ) ^ d)
	unsigned int t1 = a &b ; 
	unsigned int t2 = t1 | c ; 
	unsigned int t3 = t2 ^ d  ; 
	return ~t3 ; 

}


int main(){
	unsigned int a = 0xffffffff; 
	unsigned int b = 0x12345678; 
	unsigned int c = 0x87654321;
	unsigned int d {0x55555555}; 
	result_print(BitOps32(a,b,c,d),BitOps32(a,b,c,d));
	return 0;
}
