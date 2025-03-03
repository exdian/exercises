#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

// 整型数组按字节反向
void reverse_int_arr_byte_by_byte()
{
	int arr[8] = { 0 };
	int length = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < length; i++)
	{
		scanf("%d", arr + i);
	}

	// 想要实现的效果：0x01020304, 0x11121314, 0x21222324  --->  0x24232221, 0x14131211, 0x04030201
	// 可以看到原来放在最高 8 位的字节放在了最低 8 位，次高 8 位的字节放在了最低 8 位，所以需要实现的逻辑只是交换
	// 
	// 方案一
	// 1. 先按整个元素反向：			0x01020304, 0x11121314, 0x21222324  --->  0x21222324, 0x11121314, 0x01020304
	// 2. 再把每个元素按字节反向：	0x21222324, 0x11121314, 0x01020304  --->  0x24232221, 0x14131211, 0x04030201
	// 3. 为了避免多次遍历数组，在交换两端元素前或后对这两个元素进行按字节反向
	// 
	// 方案二
	// 直接使用 char* 来按字节交换

	{ // 方案一
		int min = 0;
		int max = length - 1;
		static void swap(int* num);
		while (min < max)
		{
			int temp = arr[min];
			arr[min] = arr[max];
			arr[max] = temp;
			swap(arr + min);
			swap(arr + max);
			min += 1;
			max -= 1;
		}

	}

	for (int i = 0; i < length; i++)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");
	{ // 方案二
		char* high = (char*)(arr + length) - 1; // arr + length 越界 1 个 int，转换成 char* 后再减 1 得到最高字节
		char* low = (char*)arr;
		while (low < high)
		{
			char temp = *low;
			*low = *high;
			*high = temp;
			low += 1;
			high -= 1;
		}

	}

	for (int i = 0; i < length; i++)
	{
		printf("%d ", arr[i]);
	}

}

static void swap(int* num)
{
	char* high = (char*)(num + 1) - 1;
	char* low = (char*)num;
	while (low < high)
	{
		char temp = *low;
		*low = *high;
		*high = temp;
		low += 1;
		high -= 1;
	}

}

// ADD 20250303
