/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:43:51 by kadam             #+#    #+#             */
/*   Updated: 2024/07/13 17:27:53 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_in_quote(char *content)
{
	if ((content[0] == '|' && content[1] == '\0') || (content[0] == '>'
			&& content[1] == '\0') || (content[0] == '>' && content[1] == '>'
			&& content[2] == '\0') || (content[0] == '<' && content[1] == '\0')
		|| (content[0] == '<' && content[1] == '<' && content[2] == '\0')
		|| (content[0] == '$' && content[1] == '\0'))
		return (1);
	return (0);
}

static int	parse_command_argument_types(t_pars *tmp)
{
	if (tmp->type == WORD && (tmp->prev == NULL || tmp->prev->type == PIPE))
		tmp->type = COMMAND;
	else if (tmp->type == WORD && is_in_quote(tmp->content) == 1)
	{
		if (tmp->prev != NULL && tmp->prev->type == FILENAME)
			tmp->type = FILENAME;
		else
			tmp->type = ARGUMENT;
	}
	else if (tmp->type == WORD && tmp->prev != NULL
		&& (tmp->prev->type == COMMAND || tmp->prev->type == ARGUMENT))
		tmp->type = ARGUMENT;
	return (tmp->type);
}

static int	parse_redirection_filename_types(t_pars *tmp)
{
	if (tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OUT
		|| tmp->type == APPEND_OUT || tmp->type == HEREDOC
		|| tmp->type == R_IN_AMB || tmp->type == R_OUT_AMB
		|| tmp->type == A_OUT_AMB)
	{
		if (tmp->next != NULL && tmp->next->type == WORD)
			tmp->next->type = FILENAME;
	}
	else if (tmp->prev != NULL && tmp->prev->type == FILENAME
		&& tmp->type == WORD)
		tmp->type = FILENAME;
	return (tmp->type);
}

void	parse_types(t_pars **x_parser)
{
	t_pars	*tmp;

	tmp = *x_parser;
	while (tmp != NULL)
	{
		if (tmp->type == DOLLAR_ENV || tmp->type == EXIT_STATUS)
			tmp->type = WORD;
		tmp = tmp->next;
	}
	tmp = *x_parser;
	while (tmp != NULL)
	{
		tmp->type = parse_command_argument_types(tmp);
		tmp->type = parse_redirection_filename_types(tmp);
		tmp = tmp->next;
	}
}
