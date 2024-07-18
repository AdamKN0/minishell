/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:57:45 by kadam             #+#    #+#             */
/*   Updated: 2024/07/11 17:45:11 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fmatch(const char *line, const char *filee)
{
	if (*line == '\0' && *filee == '\0')
		return (0);
	if (*line == UNIQCHAR)
	{
		if (fmatch(line + 1, filee) == 0 || (*filee != '\0' && fmatch(line,
					filee + 1) == 0))
			return (0);
		return (1);
	}
	if (*line == *filee)
		return (fmatch(line + 1, filee + 1));
	return (1);
}

static int	count_matches(char *line, char **files)
{
	int	i;
	int	matches;

	i = 0;
	matches = 0;
	while (files[i] != NULL)
	{
		if ((line[0] != '.' && files[i][0] == '.') || (line[0] == '.'
				&& files[i][0] != '.'))
		{
			i++;
			continue ;
		}
		if (fmatch(line, files[i]) == 0)
			matches++;
		i++;
	}
	return (matches);
}

char	**is_wildcard(char *line, char **files, int i, int j)
{
	int		matches;
	char	**arg;

	matches = count_matches(line, files);
	if (matches == 0)
		return (NULL);
	arg = (char **)malloc(sizeof(char *) * (matches + 1));
	if (arg == NULL)
		return (NULL);
	arg[matches] = NULL;
	while (files[i] != NULL)
	{
		if ((line[0] != '.' && files[i][0] == '.') || (line[0] == '.'
				&& files[i][0] != '.'))
		{
			i++;
			continue ;
		}
		if (fmatch(line, files[i]) == 0)
			arg[j++] = ft_strdup(files[i]);
		i++;
	}
	return (arg);
}

static int	count_files_in_directory(void)
{
	struct dirent	*entry;
	DIR				*dir;
	int				i;

	i = 0;
	dir = opendir(".");
	if (dir == NULL)
		return (-1);
	entry = readdir(dir);
	while (entry != NULL)
	{
		i++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (i);
}

char	**list_files_in_directory(int i, int j)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**files;

	i = count_files_in_directory();
	if (i == -1)
		return (NULL);
	files = (char **)malloc(sizeof(char *) * (i + 1));
	if (files == NULL)
		return (NULL);
	dir = opendir(".");
	if (dir == NULL)
	{
		free(files);
		return (NULL);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		files[j++] = ft_strdup(entry->d_name);
		entry = readdir(dir);
	}
	files[j] = NULL;
	closedir(dir);
	return (files);
}
