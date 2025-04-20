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

	// 快慢指针找到中点。运行到这里说明至少有 2 个节点
	void* left = *head;
	void* right = *(void**)((char*)*head + offsetof_next); // (char*)node + offsetof_next 得到下一个节点指针的地址，所以强制类型转换二级指针
	while (right != NULL && *(void**)((char*)right + offsetof_next) != NULL) // 当只有 2 个节点时不进入
	{
		left = *(void**)((char*)left + offsetof_next);
		right = *(void**)((char*)right + offsetof_next);
		right = *(void**)((char*)right + offsetof_next);
	}

	right = *(void**)((char*)left + offsetof_next);
	*(void**)((char*)left + offsetof_next) = NULL; // 切断链表
	merge_sort_linklist(head, offsetof_next, pfunc); // 递归层次最深为 log2(node_count)，向上取整。
	merge_sort_linklist(&right, offsetof_next, pfunc);
	left = *head;
	/*
	此时 left 和 right 不可能为 NULL，
	因此这里将循环的第一次展开反而性能更优，能少一次 left != NULL && right != NULL 计算，也能省去 dummy 变量，减小函数栈帧
	void* dummy = NULL;
	void* cur = &dummy;
	while (left != NULL && right != NULL)
	{
		if (pfunc(left, right) > 0)
		{
			*(void**)cur = right; // 修改 cur 指向的地址空间
			cur = (void*)((char*)right + offsetof_next); // 获取下一个节点的地址
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

	*head = cur; // 修改了链表头，只有第一次递归到最深层的那个分支修改的才是真正的 *head，其余分支都是修改了局部变量 right
	while (left != NULL && right != NULL) // 递的过程不进入，归的过程才进入。如果这里按照常见的方法封装成函数逐节点递归的话可能导致栈溢出
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

	if (NULL == *head || NULL == *(void**)((char*)*head + offsetof_next)) // (char*)node + offsetof_next 得到下一个节点指针的地址，所以是一个二级指针
	{
		return *head;
	}

	void* last = NULL;
	void* ret = NULL;
	size_t node_num = (size_t)-1; // 如果 node_num 作为函数参数那么可以指定链表区间排序
	for (size_t i = 1; i < node_num; i++)
	{
		int flag = 0;
		void* curr = *head; // 从头开始
		void* next = *(void**)((char*)*head + offsetof_next); // 获取下一节点的指针
		for (size_t j = 0; j < node_num - i; j++)
		{
			if (NULL == next) // 当发现链表数据个数小于计数变量时修改计数变量为实际值
			{
				node_num = j + 1;
				break;
			}

			if (pfunc(curr, next) > 0) // 如果返回 > 0 则交换两个元素
			{
				*(void**)((char*)curr + offsetof_next) = *(void**)((char*)next + offsetof_next); // 这里保证了即使是区间排序也不会切断链表
				*(void**)((char*)next + offsetof_next) = curr;
				if (0 == j)
				{
					*head = next; // 如果链表第一个数据发生变化
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

			next = *(void**)((char*)curr + offsetof_next); // 获取下一节点的指针
		}

		if (1 == i) // 链表最后一个数据
		{
			ret = curr;
		}

		if (0 == flag) // 如果一轮冒泡排序下来没有数据发生交换那么就是有序的
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

static int asc(const void* elem1, const void* elem2) // 升序
{
	return ((Node*)elem1)->n - ((Node*)elem2)->n > 0 ? 1 : 0;
}

static int desc(const void* elem1, const void* elem2) // 降序
{
	return ((Node*)elem2)->n - ((Node*)elem1)->n > 0 ? 1 : 0;
}

void test_sort_linklist()
{
	size_t node_num = 0;
	int chk = 0;
	do
	{
		printf("输入节点数:> ");
		chk = scanf("%zu", &node_num);
		while (getchar() != '\n');
	} while (chk != 1);

	Node* head = NULL;
	Node* last = NULL;
	if (node_num > 0)
	{
		while ((last = head = malloc(sizeof(Node))) == NULL)
		{
			printf("初始化失败，按 Enter 键重试");
			while (getchar() != '\n');
		}

		last->n = 0;
		for (size_t i = 1; i < node_num; i++)
		{
			while ((last->next = malloc(sizeof(Node))) == NULL)
			{
				printf("初始化失败，按 Enter 键重试");
				while (getchar() != '\n');
			}

			last = last->next;
			last->n = i;
		}

		last->next = NULL;
		printf("已创建 %zu 个节点的链表\n", node_num);
	}

	clock_t start = clock();
	bubble_sort_linklist(&head, offsetof(Node, next), desc);
	bubble_sort_linklist(&head, offsetof(Node, next), asc);
	clock_t end = clock();
	double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("极端状态下冒泡排序 %zu 个节点 2 次的时间: %.4lf 秒\n", node_num, cpu_time_used);
	// debug 版本中极端状态下冒泡排序 20000 个节点 2 次的时间: 2.1020 秒
	// release 版本中极端状态下冒泡排序 20000 个节点 2 次的时间: 1.0210 秒
	// release 版本中极端状态下冒泡排序 100000 个节点 2 次的时间: 35.2230 秒
	start = clock();
	merge_sort_linklist(&head, offsetof(Node, next), desc);
	merge_sort_linklist(&head, offsetof(Node, next), asc);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("极端状态下归并排序 %zu 个节点 2 次的时间: %.4lf 秒\n", node_num, cpu_time_used);
	// debug 版本中极端状态下归并排序 20000 个节点 2 次的时间: 0.0060 秒
	// release 版本中极端状态下归并排序 20000 个节点 2 次的时间: 0.0020 秒
	// release 版本中极端状态下归并排序 100000 个节点 2 次的时间: 0.0120 秒
	while (getchar() != '\n');
	while (NULL != head)
	{
		last = head;
		head = head->next;
		free(last);
	}

	head = NULL;
	last = NULL;
	printf("已释放内存\n");
	while (getchar() != '\n');
}