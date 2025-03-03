#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

// 整型数组按元素反向
void reverse_int_arr_elem_by_elem()
{
	printf("\n字符串按元素反向\n");
	int arr[8] = { 0 };
	int length = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < length; i++)
	{
		scanf("%d", arr + i);
	}

	int min = 0;
	int max = length - 1;
	while (min < max)
	{
		int temp = arr[min];
		arr[min] = arr[max];
		arr[max] = temp;
		min += 1;
		max -= 1;
	}

	for (int i = 0; i < length; i++)
	{
		printf("%d ", arr[i]);
	}

}

// ADD 20250302
// MOD 20250303
