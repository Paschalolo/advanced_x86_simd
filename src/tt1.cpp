#include <display.h>

extern "C" int AddSubI32_a(int a , int b , int c , int d);


int main(){
	int a = 10 ; 
	int b = 40 ; 
	int c = 9 ; 
	int d =6 ;
	int r1 =  (a+b) - (c+d) + 7 ; 
	int r2 = AddSubI32_a(a,b, c,d);
	DisplayResults(a, b,c,d , r1, r2);
}
