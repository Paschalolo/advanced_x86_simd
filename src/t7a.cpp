#include <cstdint>

struct __attribute__((aligned(16)))  XmmVal{
	public : 
		union
    {
        int8_t m_I8[16];
        int16_t m_I16[8];
        int32_t m_I32[4];
        int64_t m_I64[2];
	uint8_t m_U8[16];
        uint16_t m_U16[8];
        uint32_t m_U32[4];
        uint64_t m_U64[2];
        float m_F32[4];
        double m_F64[2];
	}; 
};

extern "C" void AddI16_avx(XmmVal* c1, XmmVal* c2, const XmmVal* a,
    const XmmVal* b);
extern "C" void SubI16_avx(XmmVal* c1, XmmVal* c2, const XmmVal* a,
    const XmmVal* b);

int main(){
	return 0;
	}
