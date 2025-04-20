// The use is similar to qsort
// Modify the header of the linked list and return the end of the linked list

#define _CRT_SECURE_NO_WARNINGS 1
#include <stddef.h>

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
	void* left = *head;
	void* right = *(void**)((char*)*head + offsetof_next); // (char*)node + offsetof_next �õ���һ���ڵ�ָ��ĵ�ַ������ǿ������ת������ָ��
	while (right != NULL && *(void**)((char*)right + offsetof_next) != NULL) // ��ֻ�� 2 ���ڵ�ʱ������
	{
		left = *(void**)((char*)left + offsetof_next);
		right = *(void**)((char*)right + offsetof_next);
		right = *(void**)((char*)right + offsetof_next);
	}

	right = *(void**)((char*)left + offsetof_next);
	*(void**)((char*)left + offsetof_next) = NULL; // �ж�����
	merge_sort_linklist(head, offsetof_next, pfunc); // �ݹ�������Ϊ log2(node_count)������ȡ����
	merge_sort_linklist(&right, offsetof_next, pfunc);
	left = *head;
	/*
	��ʱ left �� right ������Ϊ NULL��
	������ｫѭ���ĵ�һ��չ���������ܸ��ţ�����һ�� left != NULL && right != NULL ���㣬Ҳ��ʡȥ dummy ��������С����ջ֡
	void* dummy = NULL;
	void* cur = &dummy;
	while (left != NULL && right != NULL)
	{
		if (pfunc(left, right) > 0)
		{
			*(void**)cur = right; // �޸� cur ָ��ĵ�ַ�ռ�
			cur = (void*)((char*)right + offsetof_next); // ��ȡ��һ���ڵ�ĵ�ַ
			right = *(void**)cur;
		}
		else
		{
			*(void**)cur = left;
			cur = (void*)((char*)left + offsetof_next);
			left = *(void**)cur;
		}

	}

	*head = dummy;
	while (left != NULL)
	{
		*(void**)cur = left;
		cur = (void*)((char*)left + offsetof_next);
		left = *(void**)cur;
	}

	while (right != NULL)
	{
		*(void**)cur = right;
		cur = (void*)((char*)right + offsetof_next);
		right = *(void**)cur;
	}

	return (void*)((char*)cur - offsetof_next);
	*/
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

	*head = cur; // �޸�������ͷ��ֻ�е�һ�εݹ鵽�������Ǹ���֧�޸ĵĲ��������� *head�������֧�����޸��˾ֲ����� right
	while (left != NULL && right != NULL) // �ݵĹ��̲����룬��Ĺ��̲Ž��롣������ﰴ�ճ����ķ�����װ�ɺ�����ڵ�ݹ�Ļ����ܵ���ջ���
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
/* = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */
// example
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node
{
	size_t n;
	struct Node* next;
} Node;

static int asc(const void* elem1, const void* elem2) // ����
{
	return ((Node*)elem1)->n - ((Node*)elem2)->n > 0 ? 1 : 0;
}

static int desc(const void* elem1, const void* elem2) // ����
{
	return ((Node*)elem2)->n - ((Node*)elem1)->n > 0 ? 1 : 0;
}

void test_sort_linklist()
{
	size_t node_num = 0;
	int chk = 0;
	do
	{
		printf("����ڵ���:> ");
		chk = scanf("%zu", &node_num);
		while (getchar() != '\n');
	} while (chk != 1);

	Node* head = NULL;
	Node* last = NULL;
	if (node_num > 0)
	{
		while ((last = head = malloc(sizeof(Node))) == NULL)
		{
			printf("��ʼ��ʧ�ܣ��� Enter ������");
			while (getchar() != '\n');
		}

		last->n = 0;
		for (size_t i = 1; i < node_num; i++)
		{
			while ((last->next = malloc(sizeof(Node))) == NULL)
			{
				printf("��ʼ��ʧ�ܣ��� Enter ������");
				while (getchar() != '\n');
			}

			last = last->next;
			last->n = i;
		}

		last->next = NULL;
		printf("�Ѵ��� %zu ���ڵ������\n", node_num);
	}

	clock_t start = clock();
	bubble_sort_linklist(&head, offsetof(Node, next), desc);
	bubble_sort_linklist(&head, offsetof(Node, next), asc);
	clock_t end = clock();
	double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("����״̬��ð������ %zu ���ڵ� 2 �ε�ʱ��: %.4lf ��\n", node_num, cpu_time_used);
	// debug �汾�м���״̬��ð������ 20000 ���ڵ� 2 �ε�ʱ��: 2.1020 ��
	// release �汾�м���״̬��ð������ 20000 ���ڵ� 2 �ε�ʱ��: 1.0210 ��
	// release �汾�м���״̬��ð������ 100000 ���ڵ� 2 �ε�ʱ��: 35.2230 ��
	start = clock();
	merge_sort_linklist(&head, offsetof(Node, next), desc);
	merge_sort_linklist(&head, offsetof(Node, next), asc);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("����״̬�¹鲢���� %zu ���ڵ� 2 �ε�ʱ��: %.4lf ��\n", node_num, cpu_time_used);
	// debug �汾�м���״̬�¹鲢���� 20000 ���ڵ� 2 �ε�ʱ��: 0.0060 ��
	// release �汾�м���״̬�¹鲢���� 20000 ���ڵ� 2 �ε�ʱ��: 0.0020 ��
	// release �汾�м���״̬�¹鲢���� 100000 ���ڵ� 2 �ε�ʱ��: 0.0120 ��
	while (getchar() != '\n');
	while (NULL != head)
	{
		last = head;
		head = head->next;
		free(last);
	}

	head = NULL;
	last = NULL;
	printf("���ͷ��ڴ�\n");
	while (getchar() != '\n');
}