
//===============================================
//  INteger avx2 programming in c++ 
//===============================================
#include <cstdint>
#include <cstdio>
#include <type_traits>
#include <string>
#include <immintrin.h>
#include <iostream>
struct YmmVal ; 
extern void MathI16_avx2(YmmVal c[6] , const YmmVal* a , const YmmVal * b );
extern void MathI32_avx2(YmmVal c[6] , const YmmVal* a , const YmmVal * b );
struct __attribute__((aligned(32))) YmmVal{
	public : 	
		union {
			int8_t mI8[32] ; 
			int16_t m_I16[16];
			int32_t m_I32[8];
			int64_t m_I64[4];
			uint8_t m_UI8[32] ; 
			uint16_t m_UI16[16];
			uint32_t m_UI32[8];
			uint64_t m_UI64[4];
			float m_f32[8];
			double   m_f64[4];
		};

		template <typename T , size_t L = 32 / sizeof(T)>
		void printString(){
			uint64_t data {m_UI64[0]};
			uint64_t data1 {m_UI64[1]};
			uint64_t data2 {m_UI64[2]};
			uint64_t data3 {m_UI64[3]};
			std::cout << "\n";
			for(size_t i{0} ; i < L; ++i){
				if constexpr ((!std::is_floating_point_v<T>) && (sizeof(T) == 8) ){
					std::printf("\n Values are : \t : %d , %d , %d , %d" , data , data1, data2, data3);
				}else if((!std::is_floating_point_v<T>) && (sizeof(T) == 4)){
					std::printf("\n Values are : \t : %d , %d ,%d , %d , %d , %d, %d ,%d " , static_cast<T>(data >> 32) , static_cast<T>(data), static_cast<T>(data1>> 32), static_cast<T>(data1),static_cast<T>(data2>> 32),static_cast<T>(data2) , static_cast<T>(data3 >> 32 ), static_cast<T>(data3));
				}else{}
			}
			std::cout << std::endl ;
		}
};

void MathI16();
void MathI32();
static const std::string c_line(75,'-');

int main(){
	// MathI16(); 
	//MathI32();
}

// aligned at 32 byte boundary 
void MathI16_avx2(YmmVal c[6] , const YmmVal* a , const YmmVal * b ){
	 __m256i a_vals = _mm256_load_si256 (std::bit_cast<__m256i*>(a));	
	 __m256i b_vals =_mm256_load_si256 (std::bit_cast<__m256i*>(b));

	 __m256i add_vals =  _mm256_add_epi16( a_vals, b_vals);
	 __m256i min_vals =  _mm256_min_epi16( a_vals, b_vals);
	 __m256i max_vals =   _mm256_max_epi16( a_vals, b_vals);
	 __m256i adds_vals =  _mm256_adds_epi16( a_vals, b_vals);
	 __m256i sub_vals =  _mm256_sub_epi16( a_vals, b_vals);
	 __m256i subs_vals = _mm256_subs_epi16( a_vals, b_vals);

	 // load it into cache and bypasss memory
	_mm256_stream_si256(std::bit_cast<__m256i*>(&(c[0])) ,add_vals);
	_mm256_stream_si256(std::bit_cast<__m256i*>(&(c[1])) , min_vals);
	_mm256_stream_si256(std::bit_cast<__m256i*>(&(c[2])) , max_vals);
	_mm256_stream_si256(std::bit_cast<__m256i*>(&(c[3])) ,adds_vals);
	_mm256_stream_si256(std::bit_cast<__m256i*>(&(c[4])) ,sub_vals);
	_mm256_stream_si256(std::bit_cast<__m256i*>(&(c[5])) ,subs_vals);
}

void MathI32_avx2(YmmVal c[6] , const YmmVal* a , const YmmVal * b ){

	 __m256i a_vals = _mm256_load_si256 (std::bit_cast<__m256i*>(a));	
	 __m256i b_vals =_mm256_load_si256 (std::bit_cast<__m256i*>(b));

	 __m256i add_vals =  _mm256_add_epi32( a_vals, b_vals);
	 __m256i min_vals =  _mm256_min_epi32( a_vals, b_vals);
	 __m256i max_vals =   _mm256_max_epi32( a_vals, b_vals);
	 __m256i adds_vals =  _mm256_add_epi32( a_vals, b_vals);
	 __m256i sub_vals =  _mm256_sub_epi32( a_vals, b_vals);
	 __m256i subs_vals = _mm256_sub_epi32( a_vals, b_vals);

	 // load it into cache and bypasss memory
	_mm256_stream_si256(std::bit_cast<__m256i*>(&(c[0])) ,add_vals);
	_mm256_stream_si256(std::bit_cast<__m256i*>(&(c[1])) , min_vals);
	_mm256_stream_si256(std::bit_cast<__m256i*>(&(c[2])) , max_vals);
	_mm256_stream_si256(std::bit_cast<__m256i*>(&(c[3])) ,adds_vals);
	_mm256_stream_si256(std::bit_cast<__m256i*>(&(c[4])) ,sub_vals);
	_mm256_stream_si256(std::bit_cast<__m256i*>(&(c[5])) ,subs_vals);
}
void MathI32_avx2(YmmVal c[6] , const YmmVal* a , const YmmVal * b ){}
void MathI16(){
[[maybe_unused]]	YmmVal a , b , c[6] ;
}
void MathI32();
}
void MathI16(){
[[maybe_unused]]	YmmVal a , b , c[6] ;
}
void MathI32();
