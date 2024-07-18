/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:51:14 by kadam             #+#    #+#             */
/*   Updated: 2024/07/12 13:34:59 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_no_wildcard(t_pars **tmp, char **tmp_wild, t_pars *prev)
{
	int	i;

	if (tmp_wild == NULL || (prev && prev->type == HEREDOC))
	{
		i = 0;
		while ((*tmp)->content[i])
		{
			if ((*tmp)->content[i] == UNIQCHAR)
				(*tmp)->content[i] = '*';
			i++;
		}
		(*tmp) = (*tmp)->next;
		free_2d_array(tmp_wild, 0);
		return (1);
	}
	return (0);
}

static int	amb_red_wldc(t_pars **tmp, char **tmp_wild)
{
	int	i;

	i = 0;
	if ((*tmp)->prev && ((*tmp)->prev->type == REDIRECT_OUT
			|| (*tmp)->prev->type == REDIRECT_IN
			|| (*tmp)->prev->type == APPEND_OUT))
	{
		while (tmp_wild[i])
			i++;
		if (i > 1)
		{
			if ((*tmp)->prev->type == REDIRECT_OUT)
				(*tmp)->prev->type = A_OUT_AMB;
			else if ((*tmp)->prev->type == REDIRECT_IN)
				(*tmp)->prev->type = R_IN_AMB;
			else if ((*tmp)->prev->type == APPEND_OUT)
				(*tmp)->prev->type = A_OUT_AMB;
			(*tmp) = (*tmp)->next;
			free_2d_array(tmp_wild, 0);
			return (1);
		}
	}
	return (0);
}

static void	create_new_nodes(t_pars **tmp, char **tmp_wild, t_pars **new_node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	*new_node = NULL;
	while (tmp_wild[i])
	{
		if ((*tmp)->type == COMMAND && j == 0)
		{
			ft_lstadd_back_pars(new_node, ft_lstnew_pars(tmp_wild[i++],
					(*tmp)->type, (*tmp)->space, 0));
			j = 1;
		}
		else if (j == 1)
		{
			ft_lstadd_back_pars(new_node, ft_lstnew_pars(tmp_wild[i++],
					ARGUMENT, (*tmp)->space, 0));
		}
		else
		{
			ft_lstadd_back_pars(new_node, ft_lstnew_pars(tmp_wild[i++],
					(*tmp)->type, (*tmp)->space, 0));
		}
	}
}

static void	process_wildcard(t_pars **x_parser, t_pars **tmp, char **tmp_wild,
		t_pars *prev)
{
	t_pars	*new_node;
	t_pars	*last_new_node;

	create_new_nodes(tmp, tmp_wild, &new_node);
	new_node->prev = prev;
	if (prev)
		prev->next = new_node;
	last_new_node = new_node;
	while (last_new_node->next)
		last_new_node = last_new_node->next;
	last_new_node->next = (*tmp)->next;
	if ((*tmp)->next)
		(*tmp)->next->prev = last_new_node;
	if (!prev)
		*x_parser = new_node;
	free((*tmp)->content);
	free(*tmp);
	free_2d_array(tmp_wild, 0);
	*tmp = (*tmp)->next;
}

void	expand_wildcard(t_pars **x_parser, t_pars *tmp, char **files,
		t_pars *next)
{
	char	**tmp_wild;
	t_pars	*prev;

	while (tmp)
	{
		if (tmp->wildcard == WILDCARD)
		{
			prev = tmp->prev;
			next = tmp->next;
			tmp_wild = is_wildcard(tmp->content, files, 0, 0);
			if (handle_no_wildcard(&tmp, tmp_wild, prev))
				continue ;
			else
			{
				if (amb_red_wldc(&tmp, tmp_wild))
					continue ;
				process_wildcard(x_parser, &tmp, tmp_wild, prev);
			}
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
