// The use is similar to qsort

#include <stdio.h>

void* merge_sort_linklist(
	                      void** head, // header of linklist
	                      size_t offsetof_next, // #define offsetof(node, next) ((size_t)&((node*)0)->next)
	                      int (*pfunc)(const void* elem1, const void* elem2) // if result > 0 then swap(elem1, elem2)
	                      )
{

}

void* bubble_sort_linklist(
	                       void** head, // header of linklist
	                       size_t offsetof_next, // #define offsetof(node, next) ((size_t)&((node*)0)->next)
	                       int (*pfunc)(const void* elem1, const void* elem2) // if result > 0 then swap(elem1, elem2)
	                       )
{
	if (NULL == head)
	{
		return NULL;
	}

	if (NULL == *head || NULL == *(void**)((char*)*head + offsetof_next)) // (char*)node + offsetof_next �õ���һ���ڵ�ָ��ĵ�ַ��������һ������ָ��
	{
		return *head;
	}

	void* last = NULL;
	void* ret = NULL;
	size_t node_num = (size_t)-1; // ��� node_num ��Ϊ����������ô����ָ��������������
	for (size_t i = 1; i < node_num; i++)
	{
		int flag = 0;
		void* curr = *head; // ��ͷ��ʼ
		void* next = *(void**)((char*)*head + offsetof_next); // ��ȡ��һ�ڵ��ָ��
		for (size_t j = 0; j < node_num - i; j++)
		{
			if (NULL == next) // �������������ݸ���С�ڼ�������ʱ�޸ļ�������Ϊʵ��ֵ
			{
				node_num = j + 1;
				break;
			}

			if (pfunc(curr, next) > 0) // ������� > 0 �򽻻�����Ԫ��
			{
				*(void**)((char*)curr + offsetof_next) = *(void**)((char*)next + offsetof_next); // ���ﱣ֤�˼�ʹ����������Ҳ�����ж�����
				*(void**)((char*)next + offsetof_next) = curr;
				if (0 == j)
				{
					*head = next; // ��������һ�����ݷ����仯
				}
				else
				{
					*(void**)((char*)last + offsetof_next) = next;
				}

				flag = 1;
				last = next;
			}
			else
			{
				last = curr;
				curr = next;
			}

			next = *(void**)((char*)curr + offsetof_next); // ��ȡ��һ�ڵ��ָ��
		}

		if (1 == i) // �������һ������
		{
			ret = curr;
		}

		if (0 == flag) // ���һ��ð����������û�����ݷ���������ô���������
		{
			return ret;
		}

	}

	return ret;
}
