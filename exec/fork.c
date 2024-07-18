/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:09:53 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/18 15:05:50 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_parent_process(t_cmd *p_cmd, t_args *args)
{
	if (p_cmd->prev)
	{
		close(args->o_pipe[0]);
		close(args->o_pipe[1]);
	}
	if (p_cmd->next)
	{
		args->o_pipe[0] = args->n_pipe[0];
		args->o_pipe[1] = args->n_pipe[1];
	}
}

void	handle_pipe_dup(t_cmd *p_cmd, t_args *args)
{
	if (p_cmd->prev && !p_cmd->in)
	{
		dup2(args->o_pipe[0], STDIN_FILENO);
		close(args->o_pipe[0]);
		close(args->o_pipe[1]);
	}
	if (p_cmd->next && !p_cmd->out)
	{
		dup2(args->n_pipe[1], STDOUT_FILENO);
		close(args->n_pipe[1]);
		close(args->n_pipe[0]);
	}
}

int	check_ambiguous(t_in *in, t_out *out)
{
	while (in)
	{
		if (in->ambiguous == AMBIGUOUS)
		{
			ft_error("ambiguous redirect", 1, 1);
			return (1);
		}
		in = in->next;
	}
	while (out)
	{
		if (out->ambiguous == AMBIGUOUS)
		{
			ft_error("ambiguous redirect", 1, 1);
			return (1);
		}
		out = out->next;
	}
	return (0);
}

void	wait_for_child_processes(t_args **args)
{
	int	i;
	int	l_status;

	i = 0;
	while ((*args)->pid[i] != 0)
	{
		waitpid((*args)->pid[i], &l_status, 0);
		if (WIFEXITED(l_status))
			g_status = WEXITSTATUS(l_status);
		else if (WIFSIGNALED(l_status))
			g_status = WTERMSIG(l_status) + 128;
		i++;
	}
}

int	command_with_fork(t_cmd *p_cmd, t_env *env, t_args *args, int i)
{
	args->pid[i] = fork();
	if (args->pid[i] == -1)
		return (ft_error("fork failed", 1, 1), 1);
	if (args->pid[i] == 0)
	{
		handle_pipe_dup(p_cmd, args);
		handle_in(*p_cmd, args);
		while (p_cmd->in)
		{
			if (p_cmd->in && p_cmd->in->type != H_IN
				&& check_access_in(p_cmd->in) == 0)
				exit(1);
			p_cmd->in = p_cmd->in->next;
		}
		handle_out(*p_cmd, args);
		if (p_cmd->out && check_access_out(p_cmd->out) == 0)
			exit(1);
		if (p_cmd->cmd && is_builting(p_cmd->cmd[0]))
			exec_builtins(p_cmd, &env, args);
		execute_command(p_cmd->cmd, &env);
	}
	else
		handle_parent_process(p_cmd, args);
	return (0);
}
