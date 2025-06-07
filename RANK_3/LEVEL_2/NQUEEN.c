#include <stdlib.h>
#include <stdio.h>

int	issafe(int *tab, int row, int col)
{
	int	i = 0;
	while (i < row)
	{
		if (tab[i] == col || tab[i] + i == col + row || tab[i] - i == col - row)
			return (0);
		i++;
	}
	return (1);
}

void	solve_nqueen(int *tab, int row, int n)
{
	if (row == n)
	{
		int	i = 0;
		while (i < n)
		{
			printf("%d", tab[i]);
			if (i < n - 1)
				printf(" ");
			i++;
		}
		printf("\n");
		return ;
	}
	int	col = 0;
	while (col < n)
	{
		if (issafe(tab, row, col))
		{
			tab[row] = col;
			solve_nqueen(tab, row + 1, n);
		}
		col++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	int	n = atoi(av[1]);
	int	*tab = malloc(sizeof(int) * n);
	if (!tab)
		return (1);
	solve_nqueen(tab, 0 , n);
}