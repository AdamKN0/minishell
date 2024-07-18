/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:21:01 by kadam             #+#    #+#             */
/*   Updated: 2024/07/18 14:28:48 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_quote_content(t_lexer **ptr, char **join, int quote_type)
{
	char	*temp;

	while (*ptr != NULL && (*ptr)->type != (t_type)(quote_type))
	{
		temp = ft_strjoin(*join, (*ptr)->content);
		free(*join);
		*join = temp;
		*ptr = (*ptr)->next;
	}
}

static void	process_quote_end(t_lexer **ptr, t_pars **x_parser, char **join,
		int space)
{
	if ((*ptr)->next != NULL && (*ptr)->next->type == SPACE_X)
		space = Y_SPACE;
	if (*join != NULL)
	{
		ft_lstadd_back_pars(x_parser, ft_lstnew_pars(*join, WORD, space, 0));
		free(*join);
		*join = NULL;
	}
	if (*ptr != NULL)
		*ptr = (*ptr)->next;
}

static void	process_quotes(t_lexer **ptr, t_pars **x_parser, char *join,
		int quote_type)
{
	int	space;

	space = NO_SPACE;
	quote_type = (*ptr)->type;
	*ptr = (*ptr)->next;
	if ((*ptr)->type == (t_type)(quote_type))
	{
		if ((*ptr)->next != NULL && (*ptr)->next->type == SPACE_X)
			space = Y_SPACE;
		ft_lstadd_back_pars(x_parser, ft_lstnew_pars("", WORD, space, 1));
		*ptr = (*ptr)->next;
		return ;
	}
	process_quote_content(ptr, &join, quote_type);
	process_quote_end(ptr, x_parser, &join, space);
}

static void	process_not_quotes(t_lexer **ptr, t_pars **x_parser, int space)
{
	if ((*ptr)->next != NULL && (*ptr)->next->type == SPACE_X)
		space = Y_SPACE;
	if ((*ptr)->content[0] == '$' && (*ptr)->content[1] == '\0'
		&& (*ptr)->type == WORD && (*ptr)->quote == NO_QUOTE
		&& (*ptr)->next != NULL && ((*ptr)->next->type == DOUBLE_QUOTE
			|| (*ptr)->next->type == SINGLE_QUOTE))
		*ptr = (*ptr)->next;
	else if ((*ptr)->type == PIPE && (*ptr)->prev != NULL
		&& (*ptr)->prev->type == REDIRECT_OUT)
	{
		*ptr = (*ptr)->next;
		return ;
	}
	else if ((*ptr)->type != SPACE_X)
	{
		if (ft_strchr((*ptr)->content, '*') != NULL)
			ft_lstadd_back_pars(x_parser, ft_lstnew_pars((*ptr)->content,
					(*ptr)->type, space, 2));
		else
			ft_lstadd_back_pars(x_parser, ft_lstnew_pars((*ptr)->content,
					(*ptr)->type, space, 0));
	}
	*ptr = (*ptr)->next;
}

void	parse_tokens(t_pars **x_parser, t_lexer	*ptr)
{
	char	**files;

	while (ptr != NULL)
	{
		if (ptr->type == WORD || ptr->type == SPACE_X || ptr->type == DOLLAR_ENV
			|| ptr->type == PIPE || ptr->type == REDIRECT_OUT
			|| ptr->type == REDIRECT_IN || ptr->type == APPEND_OUT
			|| ptr->type == HEREDOC || ptr->type == EXIT_STATUS)
			process_not_quotes(&ptr, x_parser, NO_SPACE);
		else if (ptr->type == SINGLE_QUOTE || ptr->type == DOUBLE_QUOTE)
			process_quotes(&ptr, x_parser, NULL, 0);
		else
			ptr = ptr->next;
	}
	handle_ambiguous_redirection(x_parser);
	handle_env_pars(x_parser, NULL, NULL, NULL);
	parse_types(x_parser);
	process_args_parser(x_parser, NULL, *x_parser);
	remove_node(x_parser, NULL, *x_parser, NULL);
	join_arg(NULL, *x_parser, NULL);
	check_prev_export(NULL, *x_parser, 0);
	files = list_files_in_directory(0, 0);
	expand_wildcard(x_parser, *x_parser, files, NULL);
	free_2d_array(files, 0);
}
