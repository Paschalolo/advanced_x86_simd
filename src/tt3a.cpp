
#include <iostream>
#include <cstdint>
extern "C" void calcu_array (int64_t* c , const int64_t* a , const int64_t* b , size_t n );
 int main(){
	 alignas(8)int64_t aa[16]{
		1,2,3,4,
		5,6,7,8,
		9,10,11,1,
		9,10,11,12
	 };
	 alignas(8)int64_t bb[16]{
		1,2,3,4,
		5,6,7,8,
		9,10,11,1,
		9,10,11,12
	 };
	 alignas(16) int64_t cc[16] {};
	 calcu_array(&(cc[0]), &(aa[0]),&(bb[0]), 16);
	return 0;
 }
