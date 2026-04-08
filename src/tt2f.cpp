#include <cstdint>
#include <cstdio> 

extern "C" int g_NumPrimes_a ; 
extern "C" int g_SumPrimes_a ;
extern "C" int Mem_addressing(int32_t , int32_t* , int32_t* , int32_t*, int32_t*);

void DisplayResults(int32_t a , int32_t b , int32_t c , int32_t d , int32_t e){
	std::printf(" %d %d %d %d %d ", a, b,c,d,e);
}
int main(){
	g_SumPrimes_a = 0;
}
