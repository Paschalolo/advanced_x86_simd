
//-----------------------------------------------------------
// Author : Pascahl 
// Executable : a2 
//-----------------------------------------------------------
#include <cstdint>
#include <iostream> 
#include <bit>
#include <immintrin.h>
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
			size_t sz = 0 ; 
			std::cout << "\n";
			for(size_t i{0} ; i < L; ++i){
				std::cout << *reinterpret_cast<T*>(&(m_UI8[0]) + sz) << " ";
				sz += S ;
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
static void AddI16(void){
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


static void AddU16(void){
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
int main(){
	AddI16();
	AddU16();
}
