/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:40:55 by kadam             #+#    #+#             */
/*   Updated: 2024/06/12 18:02:26 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find_equal(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	process_env(t_env **expande, char *line, char *befor, char *after)
{
	int	x;

	x = 0;
	if (find_equal(line) != -1)
	{
		befor = ft_substr(line, 0, find_equal(line));
		after = ft_substr(line, find_equal(line) + 1, ft_strlen(line)
				- find_equal(line) - 1);
	}
	else
	{
		befor = ft_strdup(line);
		after = ft_strdup("");
		x = 1;
	}
	if (befor != NULL)
	{
		lstadd_back_env(expande, lstnew_env(befor, after, x));
		free(befor);
	}
	if (after != NULL)
		free(after);
}

void	expander(t_env **expander, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		process_env(expander, envp[i], NULL, NULL);
		i++;
	}
}
