// BitMap.h
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	//uint32_t：1.大小确定,是32位  2.无符号数  (这里不能用int，因为int类型可能32位可能64位，不同系统大小不同)
	uint32_t* array;  //array 是动态数组
	size_t bits;     //number of bits in the array
} BitMap;

BitMap* bitmap_create(size_t bits);
void bitmap_destroy(BitMap* bm);
void bitmap_set(BitMap* bm, size_t n); // n is a bit index
void bitmap_unset(BitMap* bm, size_t n);
bool bitmap_isset(BitMap* bm, size_t n);
void bitmap_clear(BitMap* bm);
