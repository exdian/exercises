#include <string.h>
#include <stdio.h>

// 字符串按元素反向
void reverse_char_arr_elem_by_elem()
{
	char arr[] = "abcdefg";
	int left = 0;
	int right = (int)strlen(arr) - 1;
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
