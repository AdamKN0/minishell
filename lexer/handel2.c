/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:02:41 by kadam             #+#    #+#             */
/*   Updated: 2024/07/13 16:40:47 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_s_d_quote(char *line, int *i, t_quote *quote, t_lexer **lexer)
{
	if (line[*i] == '\'')
	{
		if (*quote == NO_QUOTE)
			*quote = SINGLE;
		else if (*quote == SINGLE)
			*quote = NO_QUOTE;
		ft_lstadd_back_lex(lexer, ft_lstnew_lex("\'", SINGLE_QUOTE, SINGLE,
				NO_INSIDE));
		(*i)++;
	}
	else if (line[*i] == '\"')
	{
		if (*quote == NO_QUOTE)
			*quote = DOUBLE;
		else if (*quote == DOUBLE)
			*quote = NO_QUOTE;
		ft_lstadd_back_lex(lexer, ft_lstnew_lex("\"", DOUBLE_QUOTE, DOUBLE,
				NO_INSIDE));
		(*i)++;
	}
}

static void	handle_exit_status(t_lexer **lexer, int x, t_quote *quote, int *i)
{
	char	*itoa;

	itoa = ft_itoa(g_status);
	if (x == 1)
		ft_lstadd_back_lex(lexer, ft_lstnew_lex(itoa, EXIT_STATUS, *quote,
				NO_INSIDE));
	else if (*quote == NO_QUOTE || *quote == DOUBLE)
		ft_lstadd_back_lex(lexer, ft_lstnew_lex(itoa, EXIT_STATUS,
				*quote, NO_INSIDE));
	else if (*quote == SINGLE)
		ft_lstadd_back_lex(lexer, ft_lstnew_lex("$?", WORD, *quote, NO_INSIDE));
	(*i)++;
	free(itoa);
}

static void	handle_dollar_variable(char *line, int *i, t_quote *quote,
		t_lexer **lexer)
{
	int		start;
	char	*substr;

	start = *i - 1;
	while (line[*i] != '\0' && (ft_isalnum(line[*i]) == 1 || line[*i] == '_'))
		(*i)++;
	substr = ft_substr(line, start, (*i) - start);
	if (*i == start + 1)
		ft_lstadd_back_lex(lexer, ft_lstnew_lex(substr, WORD, *quote,
				NO_INSIDE));
	else
		ft_lstadd_back_lex(lexer, ft_lstnew_lex(substr, DOLLAR_ENV, *quote,
				NO_INSIDE));
	free(substr);
}

static void	process_dollar_sign(char *line, int *i, t_lexer **lexer,
		t_quote *quote)
{
	if (line[*i] == '$')
		(*i)++;
	else
		ft_lstadd_back_lex(lexer, ft_lstnew_lex("$", WORD, *quote, NO_INSIDE));
}

void	handle_dollar(char *line, t_quote *quote, t_lexer **lexer, t_nor1 x)
{
	char	*substr;

	if (line[*(x.i)] == '$')
	{
		(*(x.i))++;
		if (ft_is_not_special(line[*(x.i)]) == 1 && line[*(x.i)] != '?')
			process_dollar_sign(line, x.i, lexer, quote);
		else
		{
			if ((line[*(x.i)] >= '0' && line[*(x.i)] <= '9') 
				|| line[*(x.i)] == '*' || line[*(x.i)] == '@')
			{
				substr = ft_substr(line, *(x.i) - 1, 2);
				ft_lstadd_back_lex(lexer, ft_lstnew_lex(substr, DOLLAR_ENV,
						*quote, NO_INSIDE));
				free(substr);
				(*(x.i))++;
			}
			else if (line[*(x.i)] == '?')
				handle_exit_status(lexer, x.x, quote, x.i);
			else
				handle_dollar_variable(line, x.i, quote, lexer);
		}
	}
}
