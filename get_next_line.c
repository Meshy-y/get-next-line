/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarkoez <bsarkoez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 16:27:06 by bsarkoez          #+#    #+#             */
/*   Updated: 2026/11/23 15:42:03 by bsarkoez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage[fd] = read_storage(storage, fd);
	if (!storage)
		return (NULL);
	if (find_newline(storage) >= 0)
		return (get_new_line(storage));
	return (get_end_file(&storage));
}


// #include <sys/stat.h>
// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	*s;
// 	int		fd;

// 	fd = open("test.txt", O_RDONLY);
// 	s = get_next_line(fd);
// 	printf("%s\n", s);
// 	free(s);
// 	s = get_next_line(fd);
// 	printf("%s\n", s);
// 	free(s);
// 	s = get_next_line(fd);
// 	printf("%s\n", s);
// 	free(s);
// 	s = get_next_line(fd);
// 	printf("%s\n", s);
// 	free(s);
// 	s = get_next_line(fd);
// 	printf("%s\n", s);
// 	free(s);
// 	s = get_next_line(fd);
// 	printf("%s\n", s);
// 	free(s);
// 	close (fd);
// 	return (0);
// }