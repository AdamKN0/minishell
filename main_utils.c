/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:45:03 by kadam             #+#    #+#             */
/*   Updated: 2024/07/17 15:38:44 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initiliaze_struct(t_norm2 *norm2)
{
	norm2->line = NULL;
	norm2->lexer_x = NULL;
	norm2->expander_x = NULL;
	norm2->parser_x = NULL;
	norm2->parser = NULL;
	norm2->cmd = NULL;
	norm2->message = NULL;
	norm2->i = 0;
	norm2->x = 0;
	norm2->tmp = NULL;
	norm2->in = NULL;
}

void	clear_all(t_norm2 *norm2, int x, int y)
{
	free(norm2->message);
	norm2->message = NULL;
	norm2->i = 0;
	ft_lstclear_lex(&norm2->lexer_x);
	free(norm2->line);
	norm2->line = NULL;
	if (x == 0)
	{
		ft_lstclear_pars(&norm2->parser_x);
		ft_lstclear_parser(&norm2->parser);
		ft_lstclear_sender(&norm2->cmd);
	}
	if (y == 1)
		g_status = 258;
}

int	syntax_error_herdoc(t_norm2 *norm2)
{
	if (norm2->message != NULL)
	{
		norm2->tmp = norm2->cmd;
		while (norm2->tmp != NULL && norm2->i != 0)
		{
			norm2->in = norm2->tmp->in;
			while (norm2->in != NULL && norm2->i != 0)
			{
				if (norm2->in->type == H_IN)
				{
					handle_here_doc(norm2->in->input, norm2->expander_x,
						norm2->x);
					norm2->i--;
				}
				norm2->in = norm2->in->next;
			}
			norm2->tmp = norm2->tmp->next;
		}
		printf("%s", norm2->message);
		clear_all(norm2, 0, 1);
		return (1);
	}
	return (0);
}

int	process_and_free_norm2(t_norm2 *norm2)
{
	change_node(&norm2->lexer_x, &norm2->expander_x);
	parse_tokens(&norm2->parser_x, norm2->lexer_x);
	parsing(norm2->parser_x, &norm2->parser, NULL, NULL);
	join_cmd_af_file(&norm2->parser, NULL, NULL, norm2->parser);
	sender(&norm2->cmd, norm2->parser, NULL);
	if (syntax_error_herdoc(norm2) == 1)
		return (1);
	if (norm2->cmd && norm2->cmd->cmd && ft_strncmp(*norm2->cmd->cmd, "exit",
			4) != 0)
		g_status = 0;
	exec(&norm2->cmd, &norm2->expander_x, norm2->x, &norm2->exec_x);
	clear_all(norm2, 0, 0);
	return (0);
}

void	lexer_norm2_x(t_norm2 *norm2)
{
	if (lexer(norm2->line, &norm2->lexer_x, 0, 0) == 1)
		norm2->x = 1;
	else
		norm2->x = 0;
}
