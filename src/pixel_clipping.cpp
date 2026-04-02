
#include <immintrin.h>
#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <bit>
#include <iostream>
#include <sys/types.h>
struct ClipData{
	uint8_t* m_PbSrc ; // source buffer poiunter 
	uint8_t* m_PbDes;// destination buffer pointer 
	size_t m_Num_pixels;
	size_t m_NumclippedPixels;
	uint8_t m_threshold; // low threshod 
	uint8_t m_thresh_hi;// high threshold 
};


 // fake check alignemnt and args 
bool check_args(ClipData* ){return false;}


// Too long 

void __attribute__((used)) ClipPixels_avx2(ClipData* clipdata){
	if(check_args(clipdata))[[unlikely]]{
		fprintf(stderr, "Failed data");
		exit(1);}

	auto pbsrc = clipdata->m_PbSrc; 
	auto pb_des = clipdata->m_PbDes; 
	auto num_pixels = clipdata->m_Num_pixels; 
	size_t num_clipped_pixels = 0;
	uint8_t thresh_lo{clipdata->m_threshold};
	uint8_t	thresh_hi{clipdata->m_thresh_hi};
	// main for loop
	size_t i = 0 ; 
	__m256i mask_lo = _mm256_set1_epi8(static_cast<char>(thresh_lo));
	__m256i mask_hi = _mm256_set1_epi8(static_cast<char>(thresh_hi));
	// load loop to registers
	__m256i dest_reg=   _mm256_load_si256(reinterpret_cast<__m256i*>(&(pbsrc[i])));
	__m256i dest_reg1=   _mm256_load_si256(reinterpret_cast<__m256i*>(&(pbsrc[i+32])));
	__m256i dest_reg2=   _mm256_load_si256(reinterpret_cast<__m256i*>(&(pbsrc[i+64])));
	for( ; (num_pixels - i) >= 96; i += 96){
		// load rgiusters
		__m256i temp1 =  _mm256_max_epu8 (dest_reg , mask_lo ); // greater than  
		__m256i temp2 =  _mm256_max_epu8 (dest_reg1 , mask_lo ); // greater than  
		__m256i temp3 =  _mm256_max_epu8 (dest_reg2, mask_lo ); // greater than  
		__m256i des_val = _mm256_min_epu8 ( temp1,mask_hi); // less than
		__m256i des_val2 = _mm256_min_epu8 ( temp2,mask_hi); // less than
		__m256i des_val3 = _mm256_min_epu8 ( temp3,mask_hi); // less than
		 _mm256_stream_si256 (std::bit_cast<__m256i*>(&(pb_des[i])),des_val);
		 _mm256_stream_si256 (std::bit_cast<__m256i*>(&(pb_des[i+32])),des_val2);
		 _mm256_stream_si256 (std::bit_cast<__m256i*>(&(pb_des[i+64])),des_val3);
		 __m256i temp12 =_mm256_cmpeq_epi8(dest_reg , des_val);
		 __m256i temp13=_mm256_cmpeq_epi8(dest_reg , des_val);
		 __m256i temp14=_mm256_cmpeq_epi8(dest_reg , des_val);

		 int a = _mm256_movemask_epi8(temp12);
		 int b = _mm256_movemask_epi8(temp13);
		 int c = _mm256_movemask_epi8(temp14);

		unsigned int sum = std::bit_cast<unsigned int>(~a) + std::bit_cast<unsigned int>(~b) + std::bit_cast<unsigned int>(~c) ;  
		num_clipped_pixels += (96 -sum);
		if( i +96 + 95 < num_pixels){
	
		 dest_reg=   _mm256_load_si256(reinterpret_cast<__m256i*>(&(pbsrc[i+96])));
	 	dest_reg1=   _mm256_load_si256(reinterpret_cast<__m256i*>(&(pbsrc[i+128])));
		 dest_reg2=   _mm256_load_si256(reinterpret_cast<__m256i*>(&(pbsrc[i+160])));
		}
		// compare for equal 
		// store in the cache bypass cache because data isnt used again
	}
	// finsh small values 
	for(; i < num_pixels ; i++){
		uint8_t pixel = pbsrc[i];
		if(pixel < thresh_lo){
			pb_des[i] = static_cast<uint8_t>(thresh_lo); 
			num_clipped_pixels++ ; 
		}else if (pixel > thresh_lo){
			pb_des[i] = static_cast<uint8_t>(thresh_hi);
			num_clipped_pixels++;
		}else {
			pb_des[i] = pbsrc[i];
		}
	}
	clipdata->m_NumclippedPixels = num_clipped_pixels;
}
void __attribute__((used,retain))ClipPixels_cpp(ClipData* clipdata){
	if(check_args(clipdata))[[unlikely]]{
		fprintf(stderr, "Failed data");
		exit(1);
	}
	auto pbsrc = clipdata->m_PbSrc; 
	auto pb_des = clipdata->m_PbDes; 
	auto num_pixels = clipdata->m_Num_pixels; 
	size_t num_clipped_pixels = 0;
	uint8_t thresh_lo = clipdata->m_threshold; 	
	uint8_t thresh_hi = clipdata->m_thresh_hi;
	
	for(size_t i{0} ; i < num_pixels ; ++i){
		uint8_t pixel = pbsrc[i];

		if(pixel < thresh_lo){
			pb_des[i] = thresh_lo; 
			num_clipped_pixels++ ; 
		}else if (pixel > thresh_lo){
			pb_des[i] = thresh_hi;
			num_clipped_pixels++;
		}else {
			pb_des[i] = pbsrc[i];
		}

	}
	clipdata->m_NumclippedPixels = num_clipped_pixels;
}

int main(){
	std::cout << "hey";
}
