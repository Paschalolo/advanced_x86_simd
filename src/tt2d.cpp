#include <cstdio> 
extern "C" void MulI32_a(int* prod1, long long* prod2, int a, int b);                                                         
extern "C" int DivI32_a(int* quo, int* rem, int a, int b);

void result_dsiplay(int a , long long b){
	std::printf("wide = %lld normal = %d", b,a);
}
int main(){
	int a{0};
	long long b{0};

	MulI32_a(&a, &b,-101020 , 400);
	result_dsiplay(a,b);
	return 0;
}
