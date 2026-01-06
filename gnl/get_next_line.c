/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:12:51 by fgarnier          #+#    #+#             */
/*   Updated: 2025/10/17 15:33:02 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *stash)
{
	int		len;
	char	*line;

	len = 0;
	if (!stash || !*stash)
		return (NULL);
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = ft_substr(stash, 0, len);
	return (line);
}

char	*clean_stash(char *stash)
{
	int		len;
	char	*new_stash;

	len = 0;
	if (!stash)
		return (NULL);
	while (stash[len] && stash[len] != '\n')
		len++;
	if (!stash[len])
	{
		free(stash);
		return (NULL);
	}
	if (stash[len] == '\n')
		len++;
	new_stash = ft_strdup(stash + len);
	free(stash);
	return (new_stash);
}

static char	*read_loop(int fd, char *stash, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while ((!stash || !ft_strchr(stash, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(stash, buffer);
		if (!tmp)
		{
			free(stash);
			return (NULL);
		}
		free(stash);
		stash = tmp;
	}
	return (stash);
}

char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!stash)
	{
		stash = ft_strdup("");
		if (!stash)
		{
			free(buffer);
			return (NULL);
		}
	}
	stash = read_loop(fd, stash, buffer);
	free(buffer);
	if (stash && !*stash)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
		return (NULL);
	stash = clean_stash(stash);
	return (line);
}
