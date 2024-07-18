/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:58:39 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/16 16:32:31 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_it(char *str, char *command)
{
	if (ft_strncmp(str, command, ft_strlen(command)) == 0
		&& ft_strlen(str) == ft_strlen(command))
		return (1);
	return (0);
}

int	is_builting(char *str)
{
	if (is_it(str, "cd") || is_it(str, "pwd") || is_it(str, "env") || is_it(str,
			"echo") || is_it(str, "exit") || is_it(str, "export") || is_it(str,
			"unset"))
		return (1);
	return (0);
}

void	exec_builtins(t_cmd *cmd, t_env **env, t_args *args)
{
	if (is_it(cmd->cmd[0], "cd"))
		exec_cd(cmd, args->f, *env);
	else if (is_it(cmd->cmd[0], "pwd"))
		exec_pwd(cmd, args->f);
	if (is_it(cmd->cmd[0], "echo"))
		exec_echo(cmd);
	else if (is_it(cmd->cmd[0], "env"))
		exec_env(cmd, *env, args->f);
	else if (is_it(cmd->cmd[0], "exit"))
		exec_exit(cmd, args->f);
	else if (is_it(cmd->cmd[0], "export"))
		exec_export(cmd, env);
	else if (is_it(cmd->cmd[0], "unset"))
		exec_unset(cmd, env);
	if (!args->f)
		exit(g_status);
}
