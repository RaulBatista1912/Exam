#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	rip(char *str, char *arr, int left, int right, int i, int open)
{
	if (!str[i] && open == 0 && left == 0 && right == 0)
	{
		printf("%s\n", arr);
		return;
	}
	if (str[i] == '(')
	{
		if (left > 0)
		{
			arr[i] = '_';
			rip(str, arr, left - 1, right, i + 1, open);
		}
		arr[i] = '(';
		rip(str, arr, left, right, i + 1, open + 1);
	}
	else if (str[i] == ')')
	{
		if (right > 0)
		{
			arr[i] = '_';
			rip(str, arr, left, right - 1, i + 1, open);
		}
		if (open > 0)
		{
			arr[i] = ')';
			rip(str, arr, left, right, i + 1, open - 1);
		}
	}
}

int	main(int ac, char **av)
{
	int		left = 0;
	int		right = 0;
	char	*str;
	int		i = 0;

	if (ac != 2)
		return (1);
	while (av[1][i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (1);
	str[i] = '\0';
	i = 0;
	while (av[1][i])
	{
		if (av[1][i] == '(')
			left++;
		else if (av[1][i] == ')')
		{
			right++;
			if (left > 0)
			{
				left--;
				right--;
			}
		}
		i++;
	}
	printf("l : %d\nr : %d\n", left, right);
	rip(av[1], str, left, right, 0, 0);
}