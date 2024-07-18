/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:49:07 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/17 10:08:34 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_output(t_cmd *c, t_args *a, int flag)
{
	a->fd = open(c->out->output, O_WRONLY | O_CREAT | flag, 0644);
}

void	handle_in(t_cmd p_cmd, t_args *args)
{
	if (p_cmd.in)
	{
		while (p_cmd.in)
		{
			if (p_cmd.in->type == RD_IN)
				args->fd = open(p_cmd.in->input, O_RDONLY);
			else if (p_cmd.in->type == H_IN)
			{
				if (p_cmd.fd != -1)
					args->fd = p_cmd.fd;
			}
			p_cmd.in = p_cmd.in->next;
		}
		dup2(args->fd, STDIN_FILENO);
		close(args->fd);
	}
}

int	handle_out(t_cmd c, t_args *a)
{
	int	strout;

	if (c.out)
	{
		while (c.out)
		{
			if (c.out->type == RD_OUT)
				ft_output(&c, a, O_TRUNC);
			else if (c.out->type == AP_OUT)
				ft_output(&c, a, O_APPEND);
			if (c.out->next)
				close(a->fd);
			c.out = c.out->next;
		}
		strout = dup(STDOUT_FILENO);
		dup2(a->fd, STDOUT_FILENO);
		close(a->fd);
		return (strout);
	}
	return (0);
}

void	get_herdoc(t_cmd **p_cmd, t_env *env, int x)
{
	t_cmd	*tmp;
	t_in	*in;

	tmp = *p_cmd;
	tmp->fd = -1;
	while (tmp)
	{
		in = tmp->in;
		tmp->fd = -1;
		while (in)
		{
			if (in->type == H_IN)
				tmp->fd = handle_here_doc(in->input, env, x);
			in = in->next;
		}
		tmp = tmp->next;
	}
}
