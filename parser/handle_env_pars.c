/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_pars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:57:18 by kadam             #+#    #+#             */
/*   Updated: 2024/07/18 14:24:01 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	create_new_nodes(t_pars **new_node, char **split, t_pars *tmp,
		int space)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i + 1] == NULL && tmp->space == NO_SPACE)
			space = NO_SPACE;
		else
			space = Y_SPACE;
		ft_lstadd_back_pars(new_node, ft_lstnew_pars(split[i], WORD, space, 0));
		i++;
	}
}

static void	update_links(t_pars **prev, t_pars **next, t_pars *new_node,
		t_pars **x_parser)
{
	t_pars	*last_new_node;

	if (*prev)
		(*prev)->next = new_node;
	new_node->prev = *prev;
	last_new_node = new_node;
	while (last_new_node->next)
		last_new_node = last_new_node->next;
	last_new_node->next = *next;
	if (*next)
		(*next)->prev = last_new_node;
	if (!*prev)
		*x_parser = new_node;
}

static void	handle_nodes(t_pars **prev, t_pars **next, t_pars **tmp,
		t_pars **x_parser)
{
	if (*prev)
		(*prev)->next = (*tmp)->next;
	if (*next)
		(*next)->prev = *prev;
	if ((*tmp)->next)
		(*tmp)->next->prev = *prev;
	if (*prev == NULL && *x_parser)
		*x_parser = *next;
	if ((*tmp)->content)
		free((*tmp)->content);
	if (*tmp)
		free(*tmp);
}

void	handle_env_pars(t_pars **x_parser, t_pars *next, t_pars *prev,
		t_pars *new_node)
{
	t_pars	*tmp;
	char	**split;

	tmp = *x_parser;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == DOLLAR_ENV)
		{
			prev = tmp->prev;
			split = ft_split(tmp->content, ' ');
			if (cout_2d_array(split) > 1)
			{
				create_new_nodes(&new_node, split, tmp, NO_SPACE);
				update_links(&prev, &next, new_node, x_parser);
				free(tmp->content);
				free(tmp);
				new_node = NULL;
			}
			else if (tmp && tmp->content && tmp->content[0] == '\0')
				handle_nodes(&prev, &next, &tmp, x_parser);
			free_2d_array(split, 0);
		}
		tmp = next;
	}
}
