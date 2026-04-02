
#include <immintrin.h>
#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <bit>
#include <sys/types.h>
struct ClipData{
	uint8_t* m_PbSrc ; // source buffer poiunter 
	uint8_t* m_PbDes;// destination buffer pointer 
	size_t m_Num_pixels;
	size_t m_NumclippedPixels;
	uint8_t m_threshold; // low threshod 
	uint8_t m_thresh_hi;// high threshold 
};


extern "C" void ClipPixels_avx2(ClipData* clipdata);
extern "C" void ClipPixels_cpp(ClipData* clipdata);
 // fake check alignemnt and args 
bool check_args(ClipData* ){return true;}


void ClipPixels_avx2(ClipData* clipdata){
	if(check_args(clipdata))[[unlikely]]{
		fprintf(stderr, "Failed data");
		exit(1);}

	auto pbsrc = clipdata->m_PbSrc; 
	auto pb_des = clipdata->m_PbDes; 
	auto num_pixels = clipdata->m_Num_pixels; 
	size_t num_clipped_pixels = 0;
	uint64_t thresh_lo = static_cast<uint64_t>(clipdata->m_threshold);
	uint64_t thresh_hi = static_cast<uint64_t>(clipdata->m_thresh_hi);
	// main for loop
	size_t i = 0 ; 
	__m256i mask_lo =  _mm256_broadcastb_epi8( _mm_cvtsi64_si128(std::bit_cast<long long>(thresh_lo)));
	__m256i mask_hi =  _mm256_broadcastb_epi8(_mm_cvtsi64_si128(std::bit_cast<long long>(thresh_hi)));
	__m256i all_ones = _mm256_cmpeq_epi32(_mm256_setzero_si256(), _mm256_setzero_si256());
	// load loop to registers 
	for( ; (num_pixels - i) > 32; i += 32 ){
		// load rgiusters
		__m256i dest_reg=   _mm256_load_si256 (std::bit_cast<__m256i*>(pbsrc));
		__m256i m_thres_high =  _mm256_max_epu8 (dest_reg , mask_hi ); // greater than  
		__m256i m_thres_low = _mm256_min_epu8 ( dest_reg, mask_lo); // less than
		__m256i new__ = _mm256_xor_si256(_mm256_or_si256 ( m_thres_low, m_thres_high), all_ones); 
		int a = _mm256_movemask_epi8 ( new__); 
		__m256i pipe1 = _mm256_and_si256(_mm256_xor_si256(_mm256_or_si256 ( m_thres_low, m_thres_high), all_ones), dest_reg);
		m_thres_high =  _mm256_and_si256 ( dest_reg, m_thres_high);
		m_thres_low = _mm256_and_si256 ( dest_reg, m_thres_low);
		 pipe1 = _mm256_or_si256(m_thres_high,  _mm256_or_si256(m_thres_low , pipe1));
		num_clipped_pixels += (32- static_cast<size_t>(__builtin_popcount(std::bit_cast<unsigned int>(a))));
		// compare for equal 
		// store in the cache bypass cache because data isnt used again
		 _mm256_stream_si256 (std::bit_cast<__m256i*>(&(pb_des[i])),pipe1);
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
void ClipPixels_cpp(ClipData* clipdata){
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

int main(){}
