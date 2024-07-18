/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:35:43 by kadam             #+#    #+#             */
/*   Updated: 2024/07/11 19:39:57 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_lstnew_cmd(char **cmd, t_in *in, t_out *out)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->cmd = cmd;
	new->in = in;
	new->out = out;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_cmd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
}

static void	clear_in_list(t_in **lst)
{
	t_in	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free((*lst)->input);
		free(*lst);
		*lst = tmp;
	}
}

static void	clear_out_list(t_out **lst)
{
	t_out	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free((*lst)->output);
		free(*lst);
		*lst = tmp;
	}
}

void	ft_lstclear_sender(t_cmd **lst)
{
	t_cmd	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free_2d_array((*lst)->cmd, 0);
		clear_in_list(&(*lst)->in);
		clear_out_list(&(*lst)->out);
		free(*lst);
		*lst = tmp;
	}
}
