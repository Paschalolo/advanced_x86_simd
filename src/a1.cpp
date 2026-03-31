#include <immintrin.h>
#include <iostream>
#include <x86intrin.h>
void __attribute__((noinline))calcz_cpp(float* z ,const float * x , const float* y ,size_t n){
	for(size_t i{0}; i < n ; ++i){
		z[i] = x[i] + y[i]; 
	}
}

// make sure data is aligned at 64 byte boundary 
void __attribute__((noinline))calcz_avx1(float* z ,const float * x , const float* y ,size_t n){
	size_t i = 0 ; 
	for(; (n-i) >= 16; i += 16){
		__m256 total = 	 _mm256_add_ps (_mm256_load_ps (x+i),_mm256_load_ps (y+i) );
		__m256 total1 = 	 _mm256_add_ps (_mm256_load_ps (x+(i*2)),_mm256_load_ps (y+(i*2)) );
		  _mm256_stream_ps (z+i,total);
		  _mm256_stream_ps (z + (i*2),total1);
	}

	for(;i < n; ++i ){
		z[i] = x[i] + y[i];
	}

}

// always aligned on a 64 byte boundfary 
extern "C" void calcx_avx2(float* z ,const float * x , const float* y ,size_t n); 

__attribute__((aligned(64))) float ans[20]{0}; 
// Testing the function 
int main(){
	__attribute__((aligned(32))) float m_data[20] {
		1.0f , 2.0f , 3.0f , 4.0f , 5.0f ,
		6.0f ,7.0f , 8.0f , 9.0f , 10.0f , 
		11.0f  ,12.0f , 13.0f , 14.9f , 154.4f,
		16.3f, 17.23f , 18.34f, 19.33f , 20.4f
	};
	__attribute__((aligned(32))) float m_data1[20] {
		1.0f , 2.0f , 3.0f , 4.0f , 5.0f ,
		6.0f ,7.0f , 8.0f , 9.0f , 10.0f , 
		11.0f  ,12.0f , 13.0f , 14.9f , 154.4f,
		16.3f, 17.23f , 18.34f, 19.33f , 20.4f
	};
	unsigned long long times[6]{0};
	 times[0] = __rdtsc(); 
	calcz_cpp(&(ans[0]), &(m_data[0]),&(m_data1[0]), 20);	
	 times[1] = __rdtsc(); 
	 times[2] = __rdtsc(); 
	calcx_avx2(&(ans[0]), &(m_data[0]),&(m_data1[0]), 20);
	 times[3] = __rdtsc(); 
	 times[4] = __rdtsc(); 
	calcz_avx1(&(ans[0]), &(m_data[0]),&(m_data1[0]), 20);
	 times[5] = __rdtsc(); 

	for(size_t i= 0 ; i < 6 ; i+=2){
		std::cout << "function is this long " << (times[i+1] - times[i] )<< std::endl ; 
	}
}
