/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:52:04 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/16 17:46:33 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_isvalid(char *str)
{
	if (!str || !*str)
		return (1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_' && *str != '=' && *str != '/')
			return (1);
		str++;
	}
	return (0);
}

void	exec_exit(t_cmd *cmd, int f)
{
	int	i;

	i = 1;
	if (cmd->cmd[1] && !is_number(cmd->cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else if (cmd->cmd[1] && cmd->cmd[2])
		ft_error("exit: too many arguments", 1, f);
	else
	{
		if (!cmd->cmd[1])
			exit(g_status);
		else
		{
			g_status = ft_atoi(cmd->cmd[1]);
			exit(g_status % 256);
		}
	}
}
