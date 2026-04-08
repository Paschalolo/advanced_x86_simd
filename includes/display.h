#ifndef DISPLAY__
#define DISPLAY__
#include <cstdio>
void DisplayResults(int a , int b , int c , int d , int r1 , int r2){
	constexpr char nl {'\n'};
	std::printf("a = %d , b = %d , c = %d , d= %d r1 = %d , r2 = %d %c ", a, b, c, d, r1, r2,nl);
}  
#endif 
