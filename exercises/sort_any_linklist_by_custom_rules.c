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

	// 快慢指针找到中点。运行到这里说明至少有 2 个节点
	void* slow = *head;
	void* fast = *(void**)((char*)*head + offsetof_next); // (char*)node + offsetof_next 得到下一个节点指针的地址，所以强制类型转换二级指针
	while (fast != NULL && *(void**)((char*)fast + offsetof_next) != NULL) // 当只有 2 个节点时不进入
	{
		slow = *(void**)((char*)slow + offsetof_next);
		fast = *(void**)((char*)fast + offsetof_next);
		fast = *(void**)((char*)fast + offsetof_next);
	}

	void* right = *(void**)((char*)slow + offsetof_next);
	*(void**)((char*)slow + offsetof_next) = NULL; // 切断链表
	merge_sort_linklist(head, offsetof_next, pfunc); // 递归层次最深为 log2(node_count)，向上取整。
	merge_sort_linklist(&right, offsetof_next, pfunc);
	void* left = *head;
	// left 和 right 在此时不可能为 NULL
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

	*head = cur; // 修改了链表头，只有第一次递归到最深层修改的才是真正的 *head，其余分支都是修改了局部变量 right
	while (left != NULL && right != NULL) // 递的过程不进入，归的过程才进入。如果这里按照常见的方法封装成函数一个一个节点递归的话可能导致栈溢出
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
