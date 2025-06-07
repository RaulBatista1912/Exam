#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	find_subset(int *arr, int n, int target, int *subset, int subset_size, int index)
{
	if (target == 0)
	{
		for (int i = 0; i < subset_size; i++)
		{
			printf("%d", subset[i]);
			if (i < subset_size - 1)
				printf(" ");
		}
		printf("\n");
	}
	for (int i = index; i < n; i++)
	{
		subset[subset_size] = arr[i];
		find_subset(arr, n, target - arr[i], subset, subset_size + 1, i + 1);
	}
}

int	main(int ac, char **av)
{
	int	target = atoi(av[1]);
	int	n = ac - 2;
	int	*arr = malloc(sizeof(int) * n);
	int	*subset = malloc(sizeof(int) * n);

	if (ac < 3)
		return (1);
	if (!arr)
		return (1);
	if (!subset)
		return (1);
	for (int i = 0; i < n; i++)
		arr[i] = atoi(av[i + 2]);
	find_subset(arr, n, target, subset, 0, 0);
}
