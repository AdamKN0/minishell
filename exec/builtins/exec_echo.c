/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:48:44 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/18 16:38:52 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_cmd(t_cmd *cmd, int *i)
{
	int	j;

	j = 0;
	if (cmd->cmd[*i] != NULL)
	{
		if (cmd->cmd[*i][0] == '\0')
			write(1, " ", 1);
		else
		{
			while (cmd->cmd[*i][j] != '\0')
			{
				write(1, &cmd->cmd[*i][j], 1);
				j++;
			}
			if (cmd->cmd[*i + 1] != NULL)
				write(1, " ", 1);
		}
	}
}

int	process_flags(t_cmd *cmd, int *i)
{
	int	j;
	int	n_flag;

	n_flag = 0;
	while (cmd->cmd[*i] != NULL && ft_strncmp(cmd->cmd[*i], "-n", 2) == 0)
	{
		j = 2;
		while (cmd->cmd[*i][j] != '\0' && cmd->cmd[*i][j] == 'n')
			j++;
		if (cmd->cmd[*i][j] == '\0')
		{
			n_flag = 1;
			(*i)++;
		}
		else
			break ;
	}
	return (n_flag);
}

void	exec_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = process_flags(cmd, &i);
	while (cmd->cmd[i] != NULL)
	{
		print_cmd(cmd, &i);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
}
