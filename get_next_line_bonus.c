/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pako <pako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 10:19:11 by pako              #+#    #+#             */
/*   Updated: 2020/04/23 18:38:16 by pako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char **files, char *buffer, int fd)
{
	char		*temp;

	temp = ft_strdup(files[fd]);
	free(files[fd]);
	files[fd] = ft_strjoin(temp, buffer);
	free(temp);
	return (files[fd]);
}

int		ft_last_line(char **line, char **files, int fd)
{
	*line = ft_strdup(files[fd]);
	free(files[fd]);
	files[fd] = NULL;
	return (0);
}

int		ft_chop_chop(int fd, char **line, char **files, int bytes_readed)
{
	char		*temp;
	char		*jump;

	if (bytes_readed <= 0 && !files[fd])
	{
		*line = ft_strdup("");
		return (bytes_readed);
	}
	temp = ft_strdup(files[fd]);
	if (!ft_strchr(files[fd], '\n'))
	{
		free(temp);
		temp = NULL;
		return (ft_last_line(line, files, fd));
	}
	jump = ft_strchr(temp, '\n');
	*line = ft_substr(temp, 0, (ft_strlen(temp) - ft_strlen(jump)));
	free(files[fd]);
	files[fd] = ft_strdup(jump + 1);
	free(temp);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*files[4096];
	char		*buffer;
	int			bytes_readed;

	if (fd == -1 || !line
	|| !(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1)))
	|| read(fd, buffer, 0) == -1 || BUFFER_SIZE <= 0)
		return (-1);
	while ((bytes_readed = read(fd, buffer, (BUFFER_SIZE))) > 0)
	{
		buffer[bytes_readed] = '\0';
		if (!files[fd])
			files[fd] = ft_strdup(buffer);
		else
			files[fd] = ft_get_line(files, buffer, fd);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (ft_chop_chop(fd, line, files, bytes_readed));
}
