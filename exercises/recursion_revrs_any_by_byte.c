#include <assert.h>
#include <stdio.h>

// 递归实现反向任意连续数据
void* recursion_revrs_any_by_byte(void* start, void* end)
{
	assert(start && end);
	if ((char*)end - (char*)start >= 4)
	{
		recursion_revrs_any_by_byte((char*)start + 1, (char*)end - 1);
	}

	char temp = *(char*)start;
	*(char*)start = *((char*)end - 1);
	*((char*)end - 1) = temp;
	return start;
}

void test_recursion_reverse()
{
	char arr[] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, '\0' };
	printf("%s\n", (char*)recursion_revrs_any_by_byte(arr, (char*)(&arr + 1) - 1));
}