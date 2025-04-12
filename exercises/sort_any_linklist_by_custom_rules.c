// The use is similar to qsort
// Modify the header of the linked list and return the end of the linked list

#include <stdio.h>

void* merge_sort_linklist(
	                      void** head, // address of header of linklist
	                      size_t offsetof_next, // #define offsetof(node, next) ((size_t)&((node*)0)->next)
	                      int (*pfunc)(const void* elem1, const void* elem2) // if result > 0 then swap(elem1, elem2)
	                      )
{
	if (NULL == head)
	{
		return NULL;
	}

	if (NULL == *head || NULL == *(void**)((char*)*head + offsetof_next))
	{
		return *head;
	}

	// ����ָ���ҵ��е㡣���е�����˵�������� 2 ���ڵ�
	void* slow = *head;
	void* fast = *(void**)((char*)*head + offsetof_next); // (char*)node + offsetof_next �õ���һ���ڵ�ָ��ĵ�ַ������ǿ������ת������ָ��
	while (fast != NULL && *(void**)((char*)fast + offsetof_next) != NULL) // ��ֻ�� 2 ���ڵ�ʱ������
	{
		slow = *(void**)((char*)slow + offsetof_next);
		fast = *(void**)((char*)fast + offsetof_next);
		fast = *(void**)((char*)fast + offsetof_next);
	}

	void* right = *(void**)((char*)slow + offsetof_next);
	*(void**)((char*)slow + offsetof_next) = NULL; // �ж�����
	merge_sort_linklist(head, offsetof_next, pfunc); // �ݹ�������Ϊ log2(node_count)������ȡ����
	merge_sort_linklist(&right, offsetof_next, pfunc);
	void* left = *head;
	// left �� right �ڴ�ʱ������Ϊ NULL
	void* cur = NULL;
	if (pfunc(left, right) > 0)
	{
		cur = right;
		right = *(void**)((char*)right + offsetof_next);
	}
	else
	{
		cur = left;
		left = *(void**)((char*)left + offsetof_next);
	}

	*head = cur; // �޸�������ͷ��ֻ�е�һ�εݹ鵽������޸ĵĲ��������� *head�������֧�����޸��˾ֲ����� right
	while (left != NULL && right != NULL) // �ݵĹ��̲����룬��Ĺ��̲Ž��롣������ﰴ�ճ����ķ�����װ�ɺ���һ��һ���ڵ�ݹ�Ļ����ܵ���ջ���
	{
		if (pfunc(left, right) > 0)
		{
			*(void**)((char*)cur + offsetof_next) = right;
			cur = right;
			right = *(void**)((char*)right + offsetof_next);
		}
		else
		{
			*(void**)((char*)cur + offsetof_next) = left;
			cur = left;
			left = *(void**)((char*)left + offsetof_next);
		}

	}

	while (left != NULL)
	{
		*(void**)((char*)cur + offsetof_next) = left;
		cur = left;
		left = *(void**)((char*)left + offsetof_next);
	}

	while (right != NULL)
	{
		*(void**)((char*)cur + offsetof_next) = right;
		cur = right;
		right = *(void**)((char*)right + offsetof_next);
	}

	return cur;
}

void* bubble_sort_linklist(
	                       void** head, // address of header of linklist
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
