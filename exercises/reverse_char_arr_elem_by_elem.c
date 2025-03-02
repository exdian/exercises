#define _CRT_SECURE_NO_WARNINGS 1

#include <string.h>
#include <stdio.h>

// 字符串按元素反向
void reverse_char_arr_elem_by_elem()
{
	char arr[] = "abcdefg";
	int left = 0;
	int right = (int)strlen(arr) - 1;
	//for (int i = 0; i <= right; i++)
	//{
	//	scanf("%c", arr + i);
	//}

	printf("%s\n", arr);
	while (left < right)
	{
		char temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
		left += 1;
		right -= 1;
	}

	printf("%s\n", arr);
}

// ADD 20250301
// MOD 20250302
