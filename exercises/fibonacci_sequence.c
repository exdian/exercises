// 斐波那契数列 1 1 2 3 5 8 13 21 ……
// 递归
int recursion_fib_seq(int n)
{
	if (n <= 0)
		return 0;
	else
		if (n <= 2)
			return 1;
		else
			return recursion_fib_seq(n - 1) + recursion_fib_seq(n - 2);
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