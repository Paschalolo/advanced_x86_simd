
//-----------------------------------------------------------
// Author : Pascahl 
// Executable : a2 
//-----------------------------------------------------------
#include <cstdint>
#include <iostream> 
#include <bit>
#include <immintrin.h>
#include <mmintrin>
struct __attribute__((aligned(16))) XmmVal{
	public : 	
		union {
			int8_t mI8[16] ; 
			int16_t m_I16[8];
			int32_t m_I32[4];
			int64_t m_I64[2];
			uint8_t m_UI8[16] ; 
			uint16_t m_UI16[8];
			uint32_t m_UI32[4];
			uint64_t m_UI64[2];
			float m_f32[4];
			double m_f64[2];
		};

		template <typename T , size_t S = sizeof(T), size_t L = 16 / S>
		void printString(){
			constexpr size_t  ss = L/2;
			uint64_t data {m_UI64[0]};
			uint64_t data1 {m_UI64[1]};
			std::cout << "\n";
			for(size_t i{0} ; i < L; ++i){
				if (i < ss){
					std::cout << static_cast<T>(data >> (i*16)) << " ";
				}else{
					std::cout << static_cast<T>(data1 >> ((i-ss )* 16)) << " ";
				}
			}
			std::cout << std::endl ;
		}
};

extern "C"{
	// ------------------------------------------------
	// Functions below 
	// ------------------------------------------------
	void AddI16_Iavx(XmmVal* c1 , XmmVal* c2, const XmmVal* a , const XmmVal* b);
	void AddU16_Iavx(XmmVal* c1 , XmmVal* c2, const XmmVal* a , const XmmVal* b);
};
void AddI16(void){
	XmmVal a, b, c1, c2 ; 
	a.m_UI16[0] = 10 ; 
	a.m_UI16[1] = 130 ; 
	a.m_UI16[2] = 200 ; 
	a.m_UI16[3] = 3000; 
	a.m_UI16[4] = 450; 
	a.m_UI16[5] = 564 ; 
	a.m_UI16[6] = 2500 ; 
	a.m_UI16[7] = 10423 ; 
	
	b.m_UI16[0] = 1120 ; 
	b.m_UI16[1] = 42310 ; 
	b.m_UI16[2] = 1320 ; 
	b.m_UI16[3] = 1045 ; 
	b.m_UI16[4] = 1570 ; 
	b.m_UI16[5] = 18760 ; 
	b.m_UI16[6] = 17860 ; 
	b.m_UI16[7] = 1530 ;

	AddU16_Iavx(&c1,&c2,&a, &b);
	
	std::cout << "\n result for addI16 - Wraparound Addition";
	a.printString<int16_t>() ;
	b.printString<int16_t>();
	c1.printString<int16_t>();
	std::cout << "\n result for addI16 - Saturated Addition";

	a.printString<int16_t>() ;
	b.printString<int16_t>();
	c2.printString<int16_t>();
}


 void AddU16(void){
	XmmVal a, b, c1, c2 ; 
	a.m_UI16[0] = 10 ; 
	a.m_UI16[1] = 130 ; 
	a.m_UI16[2] = 200 ; 
	a.m_UI16[3] = 3000; 
	a.m_UI16[4] = 450; 
	a.m_UI16[5] = 564 ; 
	a.m_UI16[6] = 2500 ; 
	a.m_UI16[7] = 10423 ; 
	
	b.m_UI16[0] = 1120 ; 
	b.m_UI16[1] = 42310 ; 
	b.m_UI16[2] = 1320 ; 
	b.m_UI16[3] = 1045 ; 
	b.m_UI16[4] = 1570 ; 
	b.m_UI16[5] = 18760 ; 
	b.m_UI16[6] = 17860 ; 
	b.m_UI16[7] = 1530 ;

	AddI16_Iavx(&c1,&c2,&a, &b);
	
	std::cout << "\n result for addI16 - Wraparound Addition";
	a.printString<uint16_t>() ;
	b.printString<uint16_t>();
	c1.printString<uint16_t>();
	std::cout << "\n result for addI16 - Saturated Addition";

	a.printString<uint16_t>() ;
	b.printString<uint16_t>();
	c2.printString<uint16_t>();
 }


//-------------------------
// Intrinsic below 

// Aligned on 16 byte boundary 
void AddI16_Iavx(XmmVal* c1 , XmmVal* c2, const XmmVal* a , const XmmVal* b){
	 __m128i reg1 = _mm_load_si128 (std::bit_cast<__m128i*>(a)); 
	__m128i reg2 = _mm_load_si128(std::bit_cast<__m128i*>(b));

	// overflow additon 
	_mm_stream_si128(std::bit_cast<__m128i*>(c1), _mm_add_epi16( reg1, reg2)); // move data back to memory location 
	// saturated addition
	_mm_stream_si128(std::bit_cast<__m128i*>(c2),_mm_adds_epi16 ( reg1, reg2));
}

// ALigned on 16 byte boundary 
void AddU16_Iavx(XmmVal* c1 , XmmVal* c2, const XmmVal* a , const XmmVal* b){

	 __m128i reg1 = _mm_load_si128 (std::bit_cast<__m128i*>(a)); 
	__m128i reg2 = _mm_load_si128(std::bit_cast<__m128i*>(b));
	// overflow usniged additon 
	_mm_stream_si128(std::bit_cast<__m128i*>(c1), _mm_add_epi16( reg1, reg2)); 
	// saturated unsigned addition 
	_mm_stream_si128(std::bit_cast<__m128i*>(c2),_mm_adds_epu16( reg1, reg2));   
}

extern "C"{
	static void SubI32();
	static void SubI64();
	
};

void SubI32_avx(XmmVal* c , const XmmVal*a , const XmmVal* b){
	// subtracting a packed signed integrs 32 bits
	__m128i p_ans = _mm_sub_epi32( _mm_load_si128 (std::bit_cast<__m128i*>(a)), _mm_load_si128 (std::bit_cast<__m128i*>(b)));
	_mm_stream_si128(std::bit_cast<__m128i*>(c),p_ans);
}
void SubI64_avx(XmmVal* c , const XmmVal*a , const XmmVal* b){
	// subtracting a packed signed integrs 32 bits
	__m128i p_ans = _mm_sub_epi64( _mm_load_si128 (std::bit_cast<__m128i*>(a)), _mm_load_si128 (std::bit_cast<__m128i*>(b)));
	_mm_stream_si128(std::bit_cast<__m128i*>(c),p_ans);
}


[[maybe_unused]]static void SubI32(){
	XmmVal a, b ,c ; 
	a.m_I32[0] = 100000 ; b.m_I32[0] = 100; 
	a.m_I32[1] = 200 ; b.m_I32[1] = 20 ; 
	a.m_I32[2] = -30; b.m_I32[2] = 30000; 
	a.m_I32[3]  = 430000000; b.m_I32[3] = -900;
	SubI32_avx(&c , &a , &b); 
	c.printString<int32_t>();

}
[[maybe_unused]]static void SubI64(){

	XmmVal a, b ,c ; 
	a.m_I64[0] = 100000 ; b.m_I64[0] = 100; 
	a.m_I64[1] = 200 ; b.m_I64[1] = 20 ; 
	SubI64_avx(&c , &a , &b); 
	c.printString<int64_t>();

}

// ---------------------------------------------------
// Multuiplaication 
// -------------------------------------------------------
//
// // integr bitwise logiacaql shift operations 


// alignment should be on a 16 byte boundary 
void AndU16_avx(XmmVal* c , const XmmVal* a , const XmmVal* b){
	__m128i result = _mm_and_si128( _mm_load_si128(std::bit_cast<__m128i*>(a)),_mm_load_si128(std::bit_cast<__m128i*>(b)));
	 _mm_stream_si128(std::bit_cast<__m128i*>(c), result);

}
// Alignedment should be on a 16 byte boundary 
void orU16_avx(XmmVal* c , const XmmVal* a , const XmmVal* b){

	__m128i result = _mm_or_si128( _mm_load_si128(std::bit_cast<__m128i*>(a)),_mm_load_si128(std::bit_cast<__m128i*>(b)));
	 _mm_stream_si128(std::bit_cast<__m128i*>(c), result);
}


// alignement should be on a 16 byte boundary 
void XorU16_avx(XmmVal* c , const XmmVal* a , const XmmVal* b){

	__m128i result = _mm_xor_si128( _mm_load_si128(std::bit_cast<__m128i*>(a)),_mm_load_si128(std::bit_cast<__m128i*>(b)));
	 _mm_stream_si128(std::bit_cast<__m128i*>(c), result);
}
int main(){
}
