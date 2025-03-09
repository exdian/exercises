#include <stdio.h>
// �������ݰ�λ��ӡ�������λ��ʼ
void print_any_data_bit_by_bit(void* start, unsigned int num)
{
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

void test_print_byb()
{
	int temp = (int)0b10101100110011100011100011010010;
	print_any_data_bit_by_bit(&temp, (int)sizeof(temp) * 8 - 1);
}