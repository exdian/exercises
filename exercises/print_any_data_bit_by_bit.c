#include <stdio.h>
#include <assert.h>
// �������ݰ�λ��ӡ�������λ��ʼ
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

		start = (char*)start + 1; // void* ָ��Ӽ�����һ��Ҫд������
		//((char*)start)++; // notgood
		//(char*)start += 1; // notgood
	}

}

// �����λ��ʼ���ݹ�ʵ��
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