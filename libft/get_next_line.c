/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:16:35 by kadam             #+#    #+#             */
/*   Updated: 2024/07/10 20:31:13 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_from_fd(int fd, char *reminder, char *buffer)
{
	int		read_counter;
	char	*temp;

	read_counter = 1;
	while (read_counter > 0)
	{
		read_counter = read(fd, buffer, BUFFER_SIZE);
		if (read_counter == 0)
			break ;
		buffer[read_counter] = '\0';
		if (reminder == NULL)
			reminder = ft_strdup("");
		temp = reminder;
		reminder = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(reminder, '\n') != NULL)
			break ;
	}
	if (read_counter == -1)
		return (NULL);
	return (reminder);
}

static char	*next_line_remind(char *line)
{
	size_t	i;
	char	*reminder;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	reminder = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (reminder == NULL || reminder[0] == '\0')
	{
		free(reminder);
		reminder = NULL;
	}
	line[i + 1] = '\0';
	return (reminder);
}

char	*get_next_line(int fd)
{
	static char	*reminder;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(reminder);
		reminder = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL || read(fd, buffer, 0) < 0)
	{
		free(buffer);
		free(reminder);
		reminder = NULL;
		return (NULL);
	}
	line = read_from_fd(fd, reminder, buffer);
	free(buffer);
	buffer = NULL;
	if (line == NULL)
		return (NULL);
	reminder = next_line_remind(line);
	return (line);
}
