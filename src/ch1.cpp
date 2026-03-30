#include <immintrin.h>
#include <iostream> 
void calcz_cpp(float* z ,const float * x , const float* y ,size_t n){
	for(size_t i{0}; i < n ; ++i){
		z[i] = x[i] + y[i]; 
	}
}

// make sure data is aligned at 64 byte boundary 
void calcz_avx1(float* z ,const float * x , const float* y ,size_t n){
	size_t i = 0 ; 
	for(; (n-i) >= 8 ; i += 8){
		__m256 total = 	 _mm256_add_ps (_mm256_load_ps (x),_mm256_load_ps (y) );
		_mm256_store_ps(z,total);
	}

	for(;i < n; ++i ){
		z[i] = x[i] + y[i];
	}

}
