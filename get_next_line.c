/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarkoez <bsarkoez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 16:27:06 by bsarkoez          #+#    #+#             */
/*   Updated: 2026/11/10 16:51:39 by bsarkoez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int	find(char *buff)
{
	int		i;
	char	*f;

	f = "\n";
	i = 0;
	while (buff[i])
	{
		if (buff[i] == *f)
			return (i);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char static	*storage;
	char		buffer[BUFFER_SIZE + 1];
	char		*temp;
	int			f;

	if (!storage)
	{
		storage = malloc(sizeof(char) * 1);
		if (!storage)
			return (NULL);
		storage[0] = 0;
	}
	f = 1;
	while (f > 0)
	{
		if (find (storage))
		{
			temp = ft_sub (storage, 0, find (storage));
			if (!temp)
				return (NULL);
			ft_storage_clean_newline(storage, find(storage));
			return (temp);
		}
		f = read(fd, buffer, (BUFFER_SIZE));
		buffer[f] = 0;
		storage = ft_strjoin(storage, buffer);
		if (!storage)
			return (NULL);
	}
	if (storage[0] != 0 && f != -1)
	{
		temp = ft_sub (storage, 0, ft_strlen(storage));
		if (!temp)
			return (NULL);
		storage[0] = 0;
		return (temp);
	}
	return (NULL);
}

int	main(void)
{
	char	*s;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	s = get_next_line(fd);
	printf("%s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("%s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("%s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("%s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("%s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("%s\n", s);
	free(s);
	return (0);
}