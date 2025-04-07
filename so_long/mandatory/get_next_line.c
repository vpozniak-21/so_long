// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   get_next_line.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/04/07 13:38:55 by vpozniak          #+#    #+#             */
// /*   Updated: 2025/04/07 13:38:56 by vpozniak         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */


#include "./so_long.h"

// //check bytes_read > 0 side
// //line 80 is checking if it is ended cuz of \0 or \n
// // it is tricky cuz if it is \n it iterates 1 more to
// // reach after newline
// // used int deliberately for i's and j's because
// //BUFFER_SIZE has int type by default
// // in after_line and extract_line it checks !stash if the
// // buff filled successfully or not

char	*fill_buffer(int fd, char *stash)
{
	int		bytes_read;
	char	*buff;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(stash), free(buff), NULL);
		buff[bytes_read] = '\0';
		stash = ft_strjoin(stash, buff);
		if (!stash)
			return (NULL);
	}
	free(buff);
	return (stash);
}

char	*extract_line(char *stash)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i])
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*after_newline(char *stash)
{
	char	*after;
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	after = malloc(ft_strlen(stash) - i + 1);
	if (!after)
		return (NULL);
	if (stash[i] == '\n')
		i++;
	while (stash[i])
		after[j++] = stash[i++];
	after[j] = '\0';
	free(stash);
	return (after);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	stash = fill_buffer(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = after_newline(stash);
	return (line);
}