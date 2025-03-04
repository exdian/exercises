#include <stdio.h>

// 浮点型数组按字节反向
void reverse_float_arr_byte_by_byte()
{
	printf("\n浮点型数组按字节反向\n");
	float arr[] = { 12345678.0f, 23456789.0f, 34567890.0f, 45678901.0f, 56789012.0f, 67890123.0f, 78901234.0f, 89012345.0f };
	int length = sizeof(arr) / sizeof(arr[0]);
	char* low = (char*)arr;
	char* high = (char*)(arr + length) - 1;
	printf("反向前\n");
	for (int i = 0; i < length; i++)
	{
		printf("%f ", arr[i]);
	}

	printf("\n\n反向后\n");
	while (low < high)
	{
		char temp = *low;
		*low = *high;
		*high = temp;
		low += 1;
		high -= 1;
	}

	for (int i = 0; i < length; i++)
	{
		printf("%f ", arr[i]);
	}

	printf("\n\n再次反向\n");
	low = (char*)arr;
	high = (char*)(arr + length) - 1;
	while (low < high)
	{
		char temp = *low;
		*low = *high;
		*high = temp;
		low += 1;
		high -= 1;
	}

	for (int i = 0; i < length; i++)
	{
		printf("%f ", arr[i]);
	}

}