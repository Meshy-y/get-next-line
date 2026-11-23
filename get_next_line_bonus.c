/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarkoez <bsarkoez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 16:27:06 by bsarkoez          #+#    #+#             */
/*   Updated: 2026/11/23 17:02:47 by bsarkoez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	find_newline(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_new_line(char *storage)
{
	char	*line;
	int		nl;

	nl = find_newline (storage);
	line = ft_sub(storage, 0, nl + 1);
	if (!line)
		return (NULL);
	ft_storage_clean_newline(storage, nl);
	return (line);
}

char	*get_end_file(char **storage)
{
	char	*line;

	if (!*storage || (*storage)[0] == 0)
	{
		free (*storage);
		*storage = NULL;
		return (NULL);
	}
	line = *storage;
	*storage = NULL;
	return (line);
}

static char	*read_storage(char *storage, int fd)
{
	char	buffer [BUFFER_SIZE + 1];
	int		f;

	if (!storage)
	{
		storage = malloc(sizeof(char) * 1);
		if (!storage)
			return (NULL);
		storage[0] = 0;
	}
	f = 1;
	while (f > 0 && find_newline(storage) < 0)
	{
		f = read(fd, buffer, BUFFER_SIZE);
		if (f < 0)
			return (free(storage), NULL);
		buffer[f] = 0;
		storage = ft_strjoin(storage, buffer);
		if (!storage)
			return (NULL);
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	storage[fd] = read_storage(storage[fd], fd);
	if (!storage[fd])
		return (NULL);
	if (find_newline(storage[fd]) >= 0)
		return (get_new_line(storage[fd]));
	return (get_end_file(&storage[fd]));
}
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	int 	fd1;
// 	int 	fd2;
// 	int 	fd3;
// 	int 	fd4;
// 	int 	fd5;
// 	char	*s;

// 	fd1 = open("test.txt", O_RDONLY);
// 	fd2 = open("test1.txt", O_RDONLY);
// 	fd3 = open("test2.txt", O_RDONLY);
// 	fd4 = open("test3.txt", O_RDONLY);
// 	fd5 = open("test4.txt", O_RDONLY);

// 	s = get_next_line(fd1);
// 	printf("fd1: %s\n", s);
// 	free(s);
// 	s = get_next_line(fd2);
// 	printf("fd2: %s\n", s);
// 	free(s);
// 	s = get_next_line(fd3);
// 	printf("fd3: %s\n", s);
// 	free(s);
// 	s = get_next_line(fd4);
// 	printf("fd4: %s\n", s);
// 	free(s);
// 	s = get_next_line(fd5);
// 	printf("fd5: %s\n", s);
// 	free(s);
// 	s = get_next_line(fd3);
// 	printf("fd3: %s\n", s);
// 	free(s);
// 	s = get_next_line(fd1);
// 	printf("fd1: %s\n", s);
// 	free(s);
// 	s = get_next_line(fd3);
// 	printf("fd3: %s\n", s);
// 	free(s);
// 	s = get_next_line(fd5);
// 	printf("fd5: %s\n", s);
// 	free(s);

// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	close(fd4);
// 	close(fd5);
// 	return (0);
// }