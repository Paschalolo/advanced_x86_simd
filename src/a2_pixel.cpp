
#include <cstdint>
#include <cstddef>
bool CalcMinMaxU8_Cpp(uint8_t* x_min , uint8_t* x_max, const uint8_t* x , size_t n );
bool CalcMinMaxU8_avx(uint8_t* x_min , uint8_t* x_max, const uint8_t* x , size_t n );

void InitArray(uint8_t* x , size_t n , unsigned int rng_seed); 

constexpr size_t c_NumElements {10000000} ; 
constexpr unsigned int c_RngSeedVal {23};

void InitArray(uint8_t* x , size_t n , unsigned int rng_seed){
	
}
