
//===============================================
//  INteger avx2 programming in c++ 
//===============================================
#include <cstdint>
#include <cstdio>
#include <type_traits>
#include <concepts>
#include <string>
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
			constexpr size_t  ss = L/2;
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
	MathI16(); 
	MathI32();
}


void MathI16(){
	YmmVal a , b , c[6] ;
}
void MathI32();
