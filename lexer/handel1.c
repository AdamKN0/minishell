/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:03:17 by kadam             #+#    #+#             */
/*   Updated: 2024/06/12 16:31:02 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handel_w_p(char *line, int *i, t_quote *quote, t_lexer **lexer)
{
	char	*substr;
	int		start;

	if (ft_is_not_special(line[*i]) == 0)
	{
		start = *i;
		while (line[*i] != '\0' && ft_is_not_special(line[*i]) == 0)
			(*i)++;
		substr = ft_substr(line, start, (*i) - start);
		ft_lstadd_back_lex(lexer, ft_lstnew_lex(substr, WORD, *quote,
				NO_INSIDE));
		free(substr);
	}
	else if (line[*i] == '|')
	{
		if (*quote == NO_QUOTE)
			g_status = 0;
		ft_lstadd_back_lex(lexer, ft_lstnew_lex("|", PIPE, *quote,
				NO_INSIDE));
		(*i)++;
	}
}

static void	handle_out_red(char *line, int *i, t_quote *quote, t_lexer **lexer)
{
	if (line[*i + 1] == '>')
	{
		ft_lstadd_back_lex(lexer, ft_lstnew_lex(">>", APPEND_OUT, *quote,
				NO_INSIDE));
		(*i) += 2;
	}
	else
	{
		ft_lstadd_back_lex(lexer, ft_lstnew_lex(">", REDIRECT_OUT, *quote,
				NO_INSIDE));
		(*i)++;
	}
}

static void	handle_inp_red(char *line, int *i, t_quote *quote, t_lexer **lexer)
{
	if (line[*i + 1] == '<')
	{
		ft_lstadd_back_lex(lexer, ft_lstnew_lex("<<", HEREDOC, *quote,
				NO_INSIDE));
		(*i) += 2;
	}
	else
	{
		ft_lstadd_back_lex(lexer, ft_lstnew_lex("<", REDIRECT_IN, *quote,
				NO_INSIDE));
		(*i)++;
	}
}

void	handle_redirection(char *line, int *i, t_quote *quote, t_lexer **lexer)
{
	if (ft_is_space(line[*i]) == 1)
	{
		ft_lstadd_back_lex(lexer, ft_lstnew_lex(" ", SPACE_X, *quote,
				NO_INSIDE));
		(*i)++;
	}
	else if (line[*i] == '>')
		handle_out_red(line, i, quote, lexer);
	else if (line[*i] == '<')
		handle_inp_red(line, i, quote, lexer);
}
