/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:42:03 by vpozniak          #+#    #+#             */
/*   Updated: 2025/04/14 15:17:39 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

char	*extract_line(char **saved_text)
{
	size_t	i;
	char	*line;
	char	*new_saved;

	i = 0;
	while ((*saved_text)[i] && (*saved_text)[i] != '\n')
		i++;

	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while ((*saved_text)[i] && (*saved_text)[i] != '\n')
	{
		line[i] = (*saved_text)[i];
		i++;
	}
	line[i] = '\0';
	if ((*saved_text)[i] == '\n')
		i++;
	new_saved = ft_strdup(*saved_text + i);
	free(*saved_text);
	*saved_text = new_saved;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*saved_text;
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(saved_text, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		saved_text = ft_strjoin(saved_text, buffer);
	}
	free(buffer);
	if (saved_text && *saved_text)
		return (extract_line(&saved_text));
	free(saved_text);
	saved_text = NULL;
	return (NULL);
}



// char	*fill_buffer(int fd, char *stash)
// {
// 	int		bytes_read;
// 	char	*buff;

// 	buff = malloc(BUFFER_SIZE + 1);
// 	if (!buff)
// 		return (NULL);
// 	bytes_read = 1;
// 	while (bytes_read != 0 && !ft_strchr(stash, '\n'))
// 	{
// 		bytes_read = read(fd, buff, BUFFER_SIZE);
// 		if (bytes_read == -1)
// 			return (free(stash), free(buff), NULL);
// 		buff[bytes_read] = '\0';
// 		stash = ft_strjoin(stash, buff);
// 		if (!stash)
// 			return (NULL);
// 	}
// 	free(buff);
// 	return (stash);
// }

// char	*extract_line(char *stash)
// {
// 	char	*line;
// 	size_t	i;

// 	i = 0;
// 	if (!stash[0])
// 		return (NULL);
// 	while (stash[i] && stash[i] != '\n')
// 		i++;
// 	if (stash[i])
// 		i++;
// 	line = malloc(i + 1);
// 	if (!line)
// 		return (NULL);
// 	i = 0;
// 	while (stash[i] && stash[i] != '\n')
// 	{
// 		line[i] = stash[i];
// 		i++;
// 	}
// 	line[i] = '\0';
// 	return (line);
// }

// char	*after_newline(char *stash)
// {
// 	char	*after;
// 	size_t	i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (!stash)
// 		return (NULL);
// 	while (stash[i] && stash[i] != '\n')
// 		i++;
// 	if (stash[i] == '\0')
// 	{
// 		free(stash);
// 		return (NULL);
// 	}
// 	after = malloc(ft_strlen(stash) - i + 1);
// 	if (!after)
// 		return (NULL);
// 	if (stash[i] == '\n')
// 		i++;
// 	while (stash[i])
// 		after[j++] = stash[i++];
// 	after[j] = '\0';
// 	free(stash);
// 	return (after);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*stash;
// 	char		*line;

// 	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
// 		return (NULL);
// 	stash = fill_buffer(fd, stash);
// 	if (!stash)
// 		return (NULL);
// 	line = extract_line(stash);
// 	stash = after_newline(stash);
// 	return (line);
// }

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
		ptr[i++] = 0;
}
