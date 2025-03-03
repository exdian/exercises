#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

// �������鰴�ֽڷ���
void reverse_int_arr_byte_by_byte()
{
	int arr[8] = { 0 };
	int length = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < length; i++)
	{
		scanf("%d", arr + i);
	}

	// ��Ҫʵ�ֵ�Ч����0x01020304, 0x11121314, 0x21222324  --->  0x24232221, 0x14131211, 0x04030201
	// ���Կ���ԭ��������� 8 λ���ֽڷ�������� 8 λ���θ� 8 λ���ֽڷ�������� 8 λ��������Ҫʵ�ֵ��߼�ֻ�ǽ���
	// 
	// ����һ
	// 1. �Ȱ�����Ԫ�ط���			0x01020304, 0x11121314, 0x21222324  --->  0x21222324, 0x11121314, 0x01020304
	// 2. �ٰ�ÿ��Ԫ�ذ��ֽڷ���	0x21222324, 0x11121314, 0x01020304  --->  0x24232221, 0x14131211, 0x04030201
	// 3. Ϊ�˱����α������飬�ڽ�������Ԫ��ǰ����������Ԫ�ؽ��а��ֽڷ���
	// 
	// ������
	// ֱ��ʹ�� char* �����ֽڽ���

	{ // ����һ
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
	{ // ������
		char* high = (char*)(arr + length) - 1; // arr + length Խ�� 1 �� int��ת���� char* ���ټ� 1 �õ�����ֽ�
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
