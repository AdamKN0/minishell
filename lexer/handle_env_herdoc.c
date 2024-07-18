/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_herdoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:16:00 by kadam             #+#    #+#             */
/*   Updated: 2024/07/13 17:30:57 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_and_update_type(t_lexer *next)
{
	if (next->type == EXIT_STATUS && next->quote == NO_QUOTE)
	{
		free(next->content);
		next->content = ft_strdup("$?");
		next->type = WORD;
		return (0);
	}
	else if ((next->type == DOLLAR_ENV || next->type == WORD)
		&& next->quote == NO_QUOTE)
		return (next->type = WORD, 0);
	else if (next->type == EXIT_STATUS && next->quote != NO_QUOTE)
	{
		free(next->content);
		next->content = ft_strdup("$?");
		next->type = WORD;
		return (1);
	}
	else if ((next->type == DOLLAR_ENV || next->type == WORD)
		&& next->quote != NO_QUOTE)
		return (next->type = WORD, 1);
	return (0);
}

static int	handle_content(t_lexer **next)
{
	t_lexer	*tmp;

	tmp = *next;
	while (tmp != NULL && tmp->type != SPACE_X)
	{
		if ((tmp->type == PIPE || tmp->type == REDIRECT_IN
				|| tmp->type == REDIRECT_OUT || tmp->type == APPEND_OUT
				|| tmp->type == HEREDOC) && tmp->quote == NO_QUOTE
			&& tmp->inside == NO_INSIDE)
			break ;
		else if (tmp->type == DOLLAR_ENV || tmp->type == EXIT_STATUS
			|| tmp->type == WORD)
		{
			if (check_and_update_type(tmp))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	handle_env_herdoc(t_lexer **lexer)
{
	t_lexer	*tmp;
	t_lexer	*next;

	tmp = *lexer;
	while (tmp != NULL)
	{
		next = tmp->next;
		if (tmp->type == HEREDOC && tmp->quote == NO_QUOTE
			&& tmp->inside == NO_INSIDE)
		{
			while (next != NULL && next->type == SPACE_X)
				next = next->next;
			if (handle_content(&next))
				return (1);
		}
		tmp = next;
	}
	return (0);
}
