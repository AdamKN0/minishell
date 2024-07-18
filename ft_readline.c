/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:45:49 by kadam             #+#    #+#             */
/*   Updated: 2024/07/16 12:37:03 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_readline(char **line, int x, int y)
{
	*line = readline("\033[0;35mminishell 💀:\033[0m ");
	if (*line == NULL)
		exit(g_status);
	x = ft_strlen(*line);
	if (x == 0)
		return (free(*line), line = NULL, 0);
	if (x >= 1)
	{
		add_history(*line);
		while ((*line)[y] != '\0')
		{
			if (ft_is_space((*line)[y]) == 1)
				y++;
			else
				break ;
		}
		if (x == y)
			return (free(*line), line = NULL, 0);
	}
	return (1);
}
