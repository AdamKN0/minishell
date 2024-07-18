/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:38:46 by kadam             #+#    #+#             */
/*   Updated: 2024/07/02 15:48:25 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_in	*creat_node_in(char *input, t_in_type type, t_amibguous ambiguous)
{
	t_in	*new;

	new = (t_in *)malloc(sizeof(t_in));
	if (new == NULL)
		return (NULL);
	if (input == NULL)
		new->input = NULL;
	else
		new->input = ft_strdup(input);
	new->type = type;
	new->ambiguous = ambiguous;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_back_in(t_in **lst, t_in *new)
{
	t_in	*last;

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

t_out	*creat_node_out(char *output, t_out_type type, t_amibguous ambiguous)
{
	t_out	*new;

	new = (t_out *)malloc(sizeof(t_out));
	if (new == NULL)
		return (NULL);
	if (output == NULL)
		new->output = NULL;
	else
		new->output = ft_strdup(output);
	new->type = type;
	new->ambiguous = ambiguous;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_back_out(t_out **lst, t_out *new)
{
	t_out	*last;

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
