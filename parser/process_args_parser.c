/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:47:23 by kadam             #+#    #+#             */
/*   Updated: 2024/07/11 16:10:16 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_no_space_pars(t_pars *tmp)
{
	if (tmp->status == remove_it)
		tmp->status = delete_it;
	else if (tmp->status == delete_it)
		tmp->status = delete_it;
	else
		tmp->status = join_it;
}

static void	handle_y_space_pars(t_pars *tmp)
{
	if (tmp->prev && (tmp->prev->status == join_it
			|| tmp->prev->status == delete_it))
	{
		if (tmp->status == remove_it)
		{
			tmp->status = delete_it;
			if (tmp->prev)
				tmp->prev->status = break_it;
		}
		else
			tmp->status = break_it;
	}
}

void	process_args_parser(t_pars **x_parser, t_pars *next, t_pars *tmp)
{
	while (tmp != NULL)
	{
		if (tmp->status == remove_it && tmp->prev && skip_it_pars(tmp->prev))
		{
			if (tmp->next && tmp->space == NO_SPACE
				&& skip_it_pars(tmp->next) == 0)
				tmp->status = delete_it;
			else
				tmp->status = keep_it;
		}
		tmp = tmp->next;
	}
	tmp = *x_parser;
	while (tmp != NULL)
	{
		next = tmp->next;
		if (tmp->space == NO_SPACE && next)
			handle_no_space_pars(tmp);
		else if (tmp->space == Y_SPACE)
			handle_y_space_pars(tmp);
		else if (tmp->next == NULL && tmp->prev && (tmp->prev->status == join_it
				|| tmp->prev->status == delete_it))
			handle_no_space_pars(tmp);
		tmp = next;
	}
}
