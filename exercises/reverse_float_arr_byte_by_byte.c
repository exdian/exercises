#include <stdio.h>

// ���������鰴�ֽڷ���
void reverse_float_arr_byte_by_byte()
{
	printf("\n���������鰴�ֽڷ���\n");
	float arr[] = { 12345678.0f, 23456789.0f, 34567890.0f, 45678901.0f, 56789012.0f, 67890123.0f, 78901234.0f, 89012345.0f };
	int length = sizeof(arr) / sizeof(arr[0]);
	char* low = (char*)arr;
	char* high = (char*)(arr + length) - 1;
	printf("����ǰ\n");
	for (int i = 0; i < length; i++)
	{
		printf("%f ", arr[i]);
	}

	printf("\n\n�����\n");
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

	printf("\n\n�ٴη���\n");
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