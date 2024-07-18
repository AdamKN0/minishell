/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:33:01 by kadam             #+#    #+#             */
/*   Updated: 2024/07/13 17:27:20 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	modify_start(t_lexer *start, t_lexer *tmp, int x)
{
	if (x == 0)
	{
		while (start != tmp)
		{
			if (start->quote == DOUBLE)
			{
				start->inside = INSIDE_SINGLE;
				start->quote = SINGLE;
			}
			start = start->next;
		}
	}
	else if (x == 1)
	{
		while (start != tmp)
		{
			if (start->quote == SINGLE)
			{
				start->inside = INSIDE_DOUBLE;
				start->quote = DOUBLE;
			}
			start = start->next;
		}
	}
}

static void	change_to_s(t_lexer **lexer, t_lexer *start, int x)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp != NULL)
	{
		if (tmp->type == SINGLE_QUOTE)
		{
			tmp = tmp->next;
			start = tmp;
			while (tmp != NULL && tmp->type != SINGLE_QUOTE
				&& tmp->type != DOUBLE_QUOTE)
			{
				x = 1;
				tmp = tmp->next;
			}
			if (tmp != NULL && tmp->type == SINGLE_QUOTE
				&& tmp->type != DOUBLE_QUOTE && x == 1)
				modify_start(start, tmp, 0);
			x = 0;
		}
		else
			tmp = tmp->next;
	}
}

static void	change_to_d(t_lexer **lexer, t_lexer *start, int x)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp != NULL)
	{
		if (tmp->type == DOUBLE_QUOTE)
		{
			tmp = tmp->next;
			start = tmp;
			while (tmp != NULL && tmp->type != DOUBLE_QUOTE
				&& tmp->type != SINGLE_QUOTE)
			{
				x = 1;
				tmp = tmp->next;
			}
			if (tmp != NULL && tmp->type == DOUBLE_QUOTE
				&& tmp->type != SINGLE_QUOTE && x == 1)
				modify_start(start, tmp, 1);
			x = 0;
		}
		else
			tmp = tmp->next;
	}
}

static void	change_lexers_s_d(t_lexer **lexer)
{
	change_to_s(lexer, NULL, 0);
	change_to_d(lexer, NULL, 0);
}

int	lexer(char *line, t_lexer **lexer, int x, int i)
{
	t_quote	quote;
	t_nor1	nor1;

	quote = NO_QUOTE;
	while (line[i] != '\0')
	{
		handel_w_p(line, &i, &quote, lexer);
		handle_s_d_quote(line, &i, &quote, lexer);
		nor1.i = &i;
		nor1.x = x;
		handle_dollar(line, &quote, lexer, nor1);
		handle_redirection(line, &i, &quote, lexer);
	}
	change_lexers_s_d(lexer);
	if (handle_env_herdoc(lexer) == 1)
		return (1);
	return (0);
}
