// 斐波那契数列 1 1 2 3 5 8 13 21 34 55 89 144……

#include <stdio.h>
// 递归
int recursion_fib_seq_1(int n)
{
	if (n <= 2)
	{
		return 1;
	}
	else
	{
		return recursion_fib_seq_1(n - 1) + recursion_fib_seq_1(n - 2);
	}

}

// 非递归
int iteration_fib_seq(int n)
{
	int a = 1;
	int b = 1;
	int c = 1;
	for (int i = 2; i < n; i++) // n <= 2 时不进入循环
	{
		c = a + b;
		a = b;
		b = c;
	}

	return c;
}

// 优化递归
int recursion_fib_seq_2(int n, int* last)
{
	if (n <= 2)
	{
		return 1;
	}

	if (NULL == last)
	{
		int last = 0;
		return recursion_fib_seq_2(n - 1, &last) + recursion_fib_seq_2(n - 2, &last);
	}

	if (0 == *last) // 如果没到最深层
	{
		int temp1 = recursion_fib_seq_2(n - 1, last);
		int temp2 = recursion_fib_seq_2(n - 2, last);
		*last = temp1;
		return temp1 + temp2;
		*last = recursion_fib_seq_2(n - 1, last); // error
		return *last + recursion_fib_seq_2(n - 2, last); // err
	}

	return *last;
}

void test_fib_seq()
{
	for (int i = 1; i < 2920; i++)
	{
		printf("%d ", recursion_fib_seq_2(i, NULL));
		printf("%d\n", iteration_fib_seq(i));
	}

}