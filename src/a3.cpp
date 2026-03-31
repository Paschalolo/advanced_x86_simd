
#include <immintrin.h>
#include <cmath>
struct PointArray ; 
extern bool checkArgs(PointArray&);
bool CalcDistanceF64(PointArray& pa){
	if(!checkArgs(pa))return false ; 
	size_t num_points = pa.NumPoints; 

	for(size_t i{0}; i < num_points ; ++i) {
		double temp1 = pa.x1[i] - pa.x2[i];
	}
}
int main(){}
