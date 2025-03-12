#include <stdio.h>
#include <assert.h>
// 任意数据按位打印，从最低位开始
void print_any_data_bit_by_bit_1(void* start, unsigned int num)
{
	assert(start != NULL);
	while (num)
	{
		for (int i = 0; (i < 8) && (num > 0); i++)
		{
			int oup = ((*(char*)start) & (1 << i)) >> i;
			printf("%d ", oup);
			num -= 1;
		}

		start = (char*)start + 1; // void* 指针加减整数一定要写成这样
		//((char*)start)++; // notgood
		//(char*)start += 1; // notgood
	}

}

// 从最高位开始，递归实现
void print_any_data_bit_by_bit_2(void* start, unsigned int num)
{
	assert(start != NULL);
	if (num > 8)
	{
		print_any_data_bit_by_bit_2((char*)start + 1, num - 8);
	}

	int i = 7;
	if (num < 8)
	{
		i = num - 1;
	}

	for (; (i >= 0) && (num > 0); i--)
	{
		int oup = ((*(char*)start) & (1 << i)) >> i;
		printf("%d ", oup);
		num -= 1;
	}

}

void test_print_byb()
{
	int temp = (int)0b10101100110011100011100011010010;
	print_any_data_bit_by_bit_1(&temp, (int)sizeof(temp) * 8 - 1);
	printf("\n");
	print_any_data_bit_by_bit_2(&temp, (int)sizeof(temp) * 8 - 1);
}