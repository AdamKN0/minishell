/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:11:53 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/18 16:39:18 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_args(t_args *args)
{
	int	i;

	i = 0;
	args->count = 0;
	args->o_pipe[0] = -1;
	args->o_pipe[1] = -1;
	args->fd = -1;
	while (i < ARG_MAX)
	{
		args->pid[i] = 0;
		i++;
	}
	args->f = 0;
}

int	one_builtins(t_cmd *p_cmd, t_env *env, t_args *args, int strout)

{
	if (p_cmd->cmd && is_builting(p_cmd->cmd[0]) && !p_cmd->next
		&& !p_cmd->prev)
	{
		args->f = 1;
		while (p_cmd->in)
		{
			if (p_cmd->in && p_cmd->in->type != H_IN
				&& check_access_in(p_cmd->in) == 0)
				return (1);
			p_cmd->in = p_cmd->in->next;
		}
		strout = handle_out(*p_cmd, args);
		if (p_cmd->out && check_access_out(p_cmd->out) == 0)
			return (1);
		exec_builtins(p_cmd, &env, args);
		close(p_cmd->fd);
		if (strout)
		{
			dup2(strout, STDOUT_FILENO);
			close(strout);
		}
		return (1);
	}
	return (0);
}

void	execute_command(char **cmd, t_env **env)
{
	struct stat	sb;
	char		**args;
	char		*full_path;
	char		**envp;

	args = NULL;
	full_path = NULL;
	envp = env_variables(*env);
	if (!cmd)
		exit(0);
	full_path = get_full_path(cmd[0], *env);
	if (stat(full_path, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
			my_perror(cmd[0], "is a directory", 127, 0);
		else if (S_ISREG(sb.st_mode) && access(full_path, X_OK) == -1)
			my_perror(cmd[0], "Permission denied", 126, 0);
	}
	else if (ft_strchr(cmd[0], '/') || __path(*env) == NULL)
		my_perror(cmd[0], "No such file or directory", 127, 0);
	if (execve(full_path, cmd, envp) == -1)
		my_perror(cmd[0], "command not found", 127, 0);
	free(full_path);
	free(args);
}

void	close_pipe(t_args *args)
{
	wait_for_child_processes(&args);
	close(args->o_pipe[0]);
	close(args->o_pipe[1]);
	close(args->n_pipe[0]);
	close(args->n_pipe[1]);
	close(args->fd);
}

void	exec(t_cmd **cmd, t_env **env, int x, t_exec *e)
{
	e->i = 0;
	if (!cmd || !*cmd)
		return ;
	e->cmd = *cmd;
	init_args(&e->args);
	get_herdoc(cmd, *env, x);
	while (e->cmd)
	{
		e->in = e->cmd->in;
		e->out = e->cmd->out;
		if (check_ambiguous(e->in, e->out))
			e->cmd = e->cmd->next;
		else
		{
			if (pipe(e->args.n_pipe) == -1)
				ft_error("pipe failed", 1, 1);
			if (one_builtins(e->cmd, *env, &e->args, 0) == 1)
				break ;
			if (command_with_fork(e->cmd, *env, &e->args, e->i))
				break ;
			e->cmd = e->cmd->next;
			e->i++;
		}
	}
	close_pipe(&e->args);
}
