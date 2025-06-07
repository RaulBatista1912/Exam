/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:31:40 by rabatist          #+#    #+#             */
/*   Updated: 2025/05/29 17:28:17 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

void print_stars(char *str)
{
	int i = 0;
	while (str[i])
	{
		printf("*");
		i++;
	}
}

void filter(char *line, char *str)
{
	int	i = 0;
	int	j = 0;
	int	flag = 0;

	while (line[i])
	{
		j = 0;
		flag = 0;
		while (line[i + j] == str[j] && line[i + j])
		{
			if (str[j + 1] == '\0')
			{
				print_stars(str);
				i += j;
				flag = 1;
				break;
			}
			j++;
		}
		if (!flag)
			printf("%c", line[i]);
		i++;
	}
}

void read_and_process(int fd, char *str)
{
	char *buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	char *line = NULL;
	int line_len = 0;
	int bytes;

	if (!buffer)
		return;
	while ((bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{ 
		buffer[bytes] = '\0';
		for (int i = 0; i < bytes; i++)
		{
			line = realloc(line, line_len + 2);
			line[line_len] = buffer[i];
			line_len++;
			if (buffer[i] == '\n')
			{
				line[line_len] = '\0';
				filter(line, str);
				free(line);
				line = NULL;
				line_len = 0;
			}
		}
	}
	free(buffer);
	if (line)
	{
		line[line_len] = '\0';
		filter(line, str);
		free(line);
	}
}
int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	read_and_process(0, av[1]);
	return (0);
}
