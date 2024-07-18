/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:33:01 by kadam             #+#    #+#             */
/*   Updated: 2024/06/12 16:27:40 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_lstnew_lex(char *content, t_type type, t_quote quote,
		t_inside inside)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->content = ft_strdup(content);
	node->type = type;
	node->quote = quote;
	node->inside = inside;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_lstadd_back_lex(t_lexer **head, t_lexer *new)
{
	t_lexer	*last;

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

void	ft_lstclear_lex(t_lexer **head)
{
	t_lexer	*current;
	t_lexer	*next;

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

int	ft_is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_is_not_special(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '$' || ft_is_space(c) == 1
		|| c == '\'' || c == '\"' || c == '\0')
		return (1);
	return (0);
}
