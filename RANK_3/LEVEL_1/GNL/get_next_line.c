#include "get_next_line.h"

char	*ft_strchr(char *str, char c)
{
	int	i = 0;

	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	if (str[i] == c)
		return (str + i);
	return (NULL);
}

int	ft_strlen(char *str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}

char	*ft_str_join(char *s1, char *s2)
{
	int		i = 0;
	int		j = 0;
	char	*str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));

	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_str_join_and_free(char *sbuffer, char *buffer)
{
	char	*str;

	if (!sbuffer)
	{
		sbuffer = malloc(1);
		if (!sbuffer)
			return (NULL);
		sbuffer[0] = '\0';
	}
	str = ft_str_join(sbuffer, buffer);
	free (sbuffer);
	return (str);
}

char	*read_file(int fd, char *sbuffer)
{
	char	*str;
	int		byte = 1;

	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	while (byte > 0)
	{
		byte = read(fd, str, BUFFER_SIZE);
		if (byte == -1)
		{
			free (str);
			free (sbuffer);
			return (NULL);
		}
		if (byte == 0)
			break;
		str[byte] = '\0';
		sbuffer = ft_str_join_and_free(sbuffer, str);
		if (ft_strchr(sbuffer, '\n'))
			break;
	}
	free (str);
	return (sbuffer);
}

char	*ft_line(char *sbuffer)
{
	int		i = 0;
	char	*str;

	if (!sbuffer[i])
		return (NULL);
	while (sbuffer[i] && sbuffer[i] != '\n')
		i++;
	if (sbuffer[i] == '\n')
		str = malloc(sizeof(char) * (i + 2));
	else
		str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (sbuffer[i] && sbuffer[i] != '\n')
	{
		str[i] = sbuffer[i];
		i++;
	}
	if (sbuffer[i] == '\n')
	{
		str[i] ='\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*clean_buffer(char *sbuffer)
{
	int		i = 0;
	char	*str;
	int		j = 0;

	while (sbuffer[i] && sbuffer[i] != '\n')
		i++;
	if (!sbuffer[i])
	{
		free (sbuffer);
		sbuffer = (NULL);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(sbuffer) - i));
	if (!str)
		return (NULL);
	i++;
	while (sbuffer[i])
	{
		str[j] = sbuffer[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free (sbuffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free (buffer);
		buffer = (NULL);
		return (NULL);
	}
	buffer = read_file(fd, buffer);
	if (!buffer)
	{
		free (buffer);
		buffer = (NULL);
		return (NULL);
	}
	line = ft_line(buffer);
	if (!line)
		return (NULL);
	buffer = clean_buffer(buffer);
	return (line);
}

int	main(int ac, char **av)
{
	int	fd = open("text.txt", O_RDONLY);
	int	i = 1;
	char	*line = NULL;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%d : %s", i, line);
		i++;
		free (line);
	}
}