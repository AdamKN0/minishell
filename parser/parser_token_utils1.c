/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:32:01 by kadam             #+#    #+#             */
/*   Updated: 2024/07/12 14:16:34 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pars	*ft_lstnew_pars(char *content, t_type type, t_space space, int i)
{
	t_pars	*new;

	new = malloc(sizeof(t_pars));
	if (new == NULL)
		return (NULL);
	new->content = ft_strdup(content);
	new->type = type;
	new->space = space;
	if (i == 0 || i == 1)
	{
		if (i == 0)
			new->status = keep_it;
		else if (i == 1)
			new->status = remove_it;
		new->wildcard = NO_WILDCARD;
	}
	else if (i == 2)
	{
		new->status = keep_it;
		new->wildcard = WILDCARD;
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_lstadd_back_pars(t_pars **head, t_pars *new)
{
	t_pars	*last;

	if (head == NULL || new == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	new->prev = last;
	last->next = new;
}

void	ft_lstclear_pars(t_pars **head)
{
	t_pars	*current;
	t_pars	*next;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*head = NULL;
}

int	_change_it(t_pars *ptr, int export_flag)
{
	int	i;

	i = 0;
	if (export_flag == 1)
	{
		while (ptr->content[i] != '\0')
		{
			if (ptr->content[i] == UNIQCHAR)
				ptr->content[i] = '*';
			i++;
		}
		ptr->wildcard = NO_WILDCARD;
		return (1);
	}
	return (0);
}

void	check_prev_export(t_pars *prev, t_pars *ptr, int export_flag)
{
	while (ptr != NULL)
	{
		if (ptr->type == ARGUMENT && ptr->wildcard == WILDCARD)
		{
			export_flag = 0;
			prev = ptr->prev;
			while (prev != NULL)
			{
				if (prev->type == ARGUMENT)
					prev = prev->prev;
				else if (prev->type == COMMAND && ft_strncmp(prev->content,
						"export", ft_strlen(prev->content)) == 0)
				{
					export_flag = 1;
					break ;
				}
				else
					break ;
			}
			if (_change_it(ptr, export_flag) == 1)
				break ;
		}
		ptr = ptr->next;
	}
}
