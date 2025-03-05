#include <assert.h>

// 任意连续数据按字节反向
void* reverse_any_arr_byte_by_byte(void* base, void* end)
{
	assert(base && end);
	char* low = (char*)base;
	char* high = (char*)end - 1;
	while (low < high)
	{
		char temp = *low;
		*low = *high;
		*high = temp;
		low += 1;
		high -= 1;
	}

	return base;
}

// struct a arr[2];
// reverse_any_arr_byte_by_byte(arr, &arr + 1);