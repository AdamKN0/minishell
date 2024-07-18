/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifications_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:16:07 by kadam             #+#    #+#             */
/*   Updated: 2024/07/11 17:45:20 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_it_pars(t_pars *tmp)
{
	if (tmp->type == PIPE || tmp->type == REDIRECT_OUT
		|| tmp->type == REDIRECT_IN || tmp->type == APPEND_OUT
		|| tmp->type == HEREDOC || tmp->type == R_IN_AMB
		|| tmp->type == R_OUT_AMB || tmp->type == A_OUT_AMB)
		return (1);
	return (0);
}

static void	change_wildcard1(t_pars **x_parser)
{
	t_pars	*tmp;
	int		i;

	tmp = *x_parser;
	i = 0;
	while (tmp)
	{
		if (tmp->wildcard == WILDCARD)
		{
			i = 0;
			while (tmp->content[i])
			{
				if (tmp->content[i] == '*')
					tmp->content[i] = UNIQCHAR;
				i++;
			}
		}
		tmp = tmp->next;
	}
}

void	remove_node(t_pars **x_parser, t_pars *prev, t_pars *tmp, t_pars *next)
{
	while (tmp != NULL)
	{
		if (tmp->status == delete_it)
		{
			prev = tmp->prev;
			next = tmp->next;
			if (tmp->type == COMMAND && next != NULL && next->type == ARGUMENT)
				next->type = COMMAND;
			if (prev != NULL)
				prev->next = next;
			else
				*x_parser = next;
			if (next != NULL)
				next->prev = prev;
			free(tmp->content);
			free(tmp);
			if (prev != NULL)
				tmp = prev->next;
			else
				tmp = *x_parser;
		}
		else
			tmp = tmp->next;
	}
	change_wildcard1(x_parser);
}

void	join_arg(t_pars *next, t_pars *tmp, char *new_content)
{
	while (tmp != NULL && tmp->next != NULL)
	{
		next = tmp->next;
		if (tmp->status == join_it && skip_it_pars(tmp) == 0
			&& skip_it_pars(next) == 0)
		{
			new_content = ft_strjoin(tmp->content, next->content);
			free(tmp->content);
			tmp->content = new_content;
			if (next != NULL && next->status == break_it)
				tmp->status = keep_it;
			if (tmp->wildcard == WILDCARD || next->wildcard == WILDCARD)
				tmp->wildcard = WILDCARD;
			if ((tmp->type == COMMAND && next->wildcard == WILDCARD))
				tmp->wildcard = NO_WILDCARD;
			tmp->next = next->next;
			if (next->next != NULL)
				next->next->prev = tmp;
			free(next->content);
			free(next);
			new_content = NULL;
		}
		else
			tmp = tmp->next;
	}
}
