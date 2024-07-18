/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/06/12 16:38:08 by kadam             #+#    #+#             */
/*   Updated: 2024/06/12 17:52:52 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*lstnew_env(char *before_equal, char *after_equal, int x)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->before_equal = ft_strdup(before_equal);
	node->after_equal = ft_strdup(after_equal);
	node->export = x;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	lstadd_back_env(t_env **head, t_env *new)
{
	t_env	*last;

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

void	ft_lstclear_env(t_env **head)
{
	t_env	*current;
	t_env	*next;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->after_equal);
		free(current->before_equal);
		free(current);
		current = next;
	}
	*head = NULL;
}
