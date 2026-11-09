/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarkoez <bsarkoez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 16:27:06 by bsarkoez          #+#    #+#             */
/*   Updated: 2026/11/09 18:17:31 by bsarkoez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	char static	*line;
	char		buffer[BUFFER_SIZE + 1];
	char		*temp;
	int			f;

	line = malloc(sizeof(char) * 1);
	f = 1;
	while (f > 0)
	{
		f = read(fd, buffer, BUFFER_SIZE);
		buffer[f] = 0;
		line = ft_strjoin(line, buffer);
	}
	return (line);
	// printf("%s", buffer);
	// return (NULL);
	// while (read(fd, buffer, BUFFER_SIZE) != 0)
	// {
	// 	printf("X\n");
	// 	line = buffer;
	// }
	// return (line);
}

// char	line(char *temp, char *line)
// {
// 	char	*new;

// 	new = ft_strjoin(temp, line);
// 	free (temp);
// 	free (line);
// 	return (new);
// }


int	main(void)
{
	char	*s;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	s = get_next_line(fd);
	printf("%s", s);
	// while (s)
	// {
	// 	s = get_next_line(fd);
	// 	printf("%s", s);
	// }
	return (0);
}