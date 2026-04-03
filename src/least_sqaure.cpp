
/*
 *	Author : Pascahl Ahanmisi 
 *	Executable : Least square 
 * */
#include <cmath>
#include <immintrin.h>
#include <cstdlib>
#include <bit>
bool checkArgs(const double*, const double* , size_t ){return true ;}
constexpr double c_LsEpsilon = 1.0e-12;
void Calc_least_square_cpp( double*  m,  double* b , const double* x , const double* y  , size_t n ){
	*m = 0.0 ; 
	*b = 0.0 ; 
	if(!checkArgs(x,y,n))[[unlikely]]  exit(1);
	double zn = static_cast<double>(n);
	double sum_x {0.0} , sum_y{0.0}, sum_xx{0.0}, sum_xy{0.0};

	for(size_t i{0} ; i < n; i++){
		sum_x += x[i];
		sum_y += y[i];
		sum_xx += x[i] * x[i];
		sum_xy += x[i] * y[i];
	}
	double denom = (zn * sum_xx) - (sum_x * sum_x);
	if(fabs(denom) >= c_LsEpsilon){
		*m = (zn * sum_xy - sum_x * sum_y)/ denom;
		*b = (sum_xx * sum_y - sum_x * sum_xy)/ denom;
	}
}
void Calc_least_square_avx( double*  m,  double* b , const double* x , const double* y  , size_t n ){

	*m = 0.0 ; 
	*b = 0.0 ; 
	if(!checkArgs(x,y,n))[[unlikely]]  exit(1);
	double zn = static_cast<double>(n);
	double sum_x{0.0} , sum_y{0.0}, sum_xx{0.0}, sum_xy{0.0};
	size_t i {0};
	__m256d temp1 , tempy1 ,temp_mul2 , temp_mulxy2;
	for( ; (n-i) >= 4; i+= 4 ){
		// load 
		__m256d sum_x_P = _mm256_load_pd (x);
		__m256d sum_y_P = _mm256_load_pd (y);
		__m256d temp = _mm256_add_pd (std::bit_cast<__m256d>(_mm256_bsrli_epi128(std::bit_cast<__m256i>(sum_x_P),16)), sum_x_P);
		 temp1 = _mm256_add_pd (std::bit_cast<__m256d>(_mm256_bsrli_epi128(std::bit_cast<__m256i>(temp),8)), temp);

		__m256d tempy = _mm256_add_pd (std::bit_cast<__m256d>(_mm256_bsrli_epi128(std::bit_cast<__m256i>(sum_y_P),16)), sum_y_P);
		tempy1 = _mm256_add_pd (std::bit_cast<__m256d>(_mm256_bsrli_epi128(std::bit_cast<__m256i>(tempy),8)), tempy);
		// sum_x += x[i];
		// sum_y += y[i];
		
		//sum_xx += x[i] * x[i];
		 __m256d mul_x =_mm256_mul_pd (sum_x_P, sum_x_P);
		__m256d temp_mul1 = _mm256_add_pd (std::bit_cast<__m256d>(_mm256_bsrli_epi128(std::bit_cast<__m256i>(mul_x),16)), mul_x);
		 temp_mul2 = _mm256_add_pd (std::bit_cast<__m256d>(_mm256_bsrli_epi128(std::bit_cast<__m256i>(temp_mul1),8)),temp_mul1 );
		// sum_xy += x[i] * y[i];

		 __m256d mul_xy =_mm256_mul_pd (sum_x_P, sum_y_P);
		__m256d temp_mulxy1 = _mm256_add_pd (std::bit_cast<__m256d>(_mm256_bsrli_epi128(std::bit_cast<__m256i>(mul_xy),16)), mul_xy);
		temp_mulxy2 = _mm256_add_pd (std::bit_cast<__m256d>(_mm256_bsrli_epi128(std::bit_cast<__m256i>(temp_mulxy1),8)),temp_mulxy1 );
	}
	for(; i < n ;i++){}
	double denom ; 
	double tempo{0} ;

	//double denom = (zn * sum_xx) - (sum_x * sum_x);
	__asm__ volatile(
			".intel_syntax noprefix\n\t"
			"vmulsd %0 , %1 , %x2\n\t"
			"vmulsd %4 , %x3 , %x3\n\t"
			"vsubsd %0 , %0 , %4\n\t"
			".att_syntax\n\t"
				: "+x"(denom)
				: "x" (zn), "x"(temp_mul2) , "x"(temp1), "x"(tempo)
				:"cc"
			);
	if(fabs(denom) >= c_LsEpsilon){
		*m = (zn * sum_xy - sum_x * sum_y)/ denom;
		*b = (sum_xx * sum_y - sum_x * sum_xy)/ denom;
	}

}
int main(){
	return 0;
}
