#include <assert.h>

// 任意连续数据按位反向
void* reverse_any_arr_bit_by_bit(void* start, void* end)
{
	assert(start && end);
	char* low = (char*)start;
	char* high = (char*)end - 1;
	while (low < high)
	{
		char temp = 0;
		for (int i = 0; i < 8; i++)
		{
			temp <<= 1;
			temp |= (*low & 1 << i) >> i; // 按位取出 low 指向的字节的位放在 temp 的最低位
		} // 经过 8 轮循环后，low 指向的字节的最高位放在了 temp 的最低位

		*low = 0;
		for (int i = 0; i < 8; i++)
		{
			*low <<= 1;
			*low |= (*high & 1 << i) >> i;
		} // 经过 8 轮循环后，high 指向的字节的最高位放在了 low 的最低位

		*high = temp;
		low += 1;
		high -= 1;
	}

	if (low == high) // 如果要处理的字节数是奇数则进入
	{
		char temp = 0;
		for (int i = 0; i < 8; i++)
		{
			temp <<= 1;
			temp |= (*low & 1 << i) >> i;
		}

		*low = temp;
	}

	return start;
}
// reverse_any_arr_bit_by_bit(arr, &arr + 1);