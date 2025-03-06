#include <assert.h>

// �����������ݰ�λ����
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
			temp |= (*low & 1 << i) >> i; // ��λȡ�� low ָ����ֽڵ�λ���� temp �����λ
		} // ���� 8 ��ѭ����low ָ����ֽڵ����λ������ temp �����λ

		*low = 0;
		for (int i = 0; i < 8; i++)
		{
			*low <<= 1;
			*low |= (*high & 1 << i) >> i;
		} // ���� 8 ��ѭ����high ָ����ֽڵ����λ������ low �����λ

		*high = temp;
		low += 1;
		high -= 1;
	}

	if (low == high) // ���Ҫ������ֽ��������������
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