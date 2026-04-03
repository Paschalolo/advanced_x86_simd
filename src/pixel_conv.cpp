/*
 *	Author : Paschal Ahanmisi 
 *	Executable : Pixel COnversions 
 *
 * */
// HEaders 
#include <cstddef>
#include <cstdint>
#include <cstdlib>
bool checkAlignment(float* , const uint8_t*){return false;}

alignas(32)float g_LUT_U8ToF32[256];
void ConvertU8toU32_cpp(float* pd_des , const uint8_t*pb_src , size_t num_pixels ){
	if(checkAlignment(pd_des, pb_src))[[unlikely]] exit(1);
	
	const float* lut = &(g_LUT_U8ToF32[0]);
	for(size_t i{0} ; i < num_pixels; ++i){
		pd_des[i] = lut[pb_src[i]];
	}
}
void ConvertU8ToU32_avx(float* pd_des , const uint8_t*pb_src , size_t num_pixels){
	
	if(checkAlignment(pd_des, pb_src))[[unlikely]] exit(1);

	size_t i{0}; 

	const float* lut = &(g_LUT_U8ToF32[0]);
	for(; num_pixels-i >= 32 ; i+= 32){

	};

	for(; i < num_pixels;i++){
		pd_des[i] = lut[pb_src[i]];
	};
}
int main(){
	return 0 ;
}
