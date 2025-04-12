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
