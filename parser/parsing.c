/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:51:38 by kadam             #+#    #+#             */
/*   Updated: 2024/07/11 19:33:57 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_command(t_pars *pars, t_parser **parser_x,
		t_command **command)
{
	*command = malloc(sizeof(t_command));
	if (*command == NULL)
		return ;
	(*command)->command = ft_strdup(pars->content);
	(*command)->args = NULL;
	if ((pars->next && pars->next->type != ARGUMENT) || pars->next == NULL)
	{
		ft_lstadd_back_parser(parser_x, ft_lstnew_parser(*command, NULL, NULL));
		*command = NULL;
	}
}

static void	handle_argument(t_pars **pars, t_parser **parser_x,
		t_command **command)
{
	int	count;
	int	i;

	count = 0;
	count = count_node(*pars, ARGUMENT);
	(*command)->args = malloc(sizeof(char *) * (count + 1));
	if ((*command)->args == NULL)
		return ;
	i = 0;
	while (i < count)
	{
		(*command)->args[i] = ft_strdup((*pars)->content);
		*pars = (*pars)->next;
		i++;
	}
	(*command)->args[count] = NULL;
	ft_lstadd_back_parser(parser_x, ft_lstnew_parser(*command, NULL, NULL));
	*command = NULL;
}

static void	handle_redir(t_pars *pars, t_parser **parser_x, t_redirection **red)
{
	*red = malloc(sizeof(t_redirection));
	if (*red == NULL)
		return ;
	(*red)->redirection = ft_strdup(pars->content);
	(*red)->file = NULL;
	if (pars->type == R_IN_AMB || pars->type == R_OUT_AMB
		|| pars->type == A_OUT_AMB)
		(*red)->ambiguous = AMBIGUOUS;
	else
		(*red)->ambiguous = NO_AMBIGUOUS;
	if (pars->type == REDIRECT_IN || pars->type == R_IN_AMB)
		(*red)->type = REDIRECT_IN_e;
	else if (pars->type == REDIRECT_OUT || pars->type == R_OUT_AMB)
		(*red)->type = REDIRECT_OUT_e;
	else if (pars->type == APPEND_OUT || pars->type == A_OUT_AMB)
		(*red)->type = APPEND_OUT_e;
	else if (pars->type == HEREDOC)
		(*red)->type = HEREDOC_e;
	if ((pars->next && pars->next->type != FILENAME) || pars->next == NULL)
	{
		if (pars->type != HEREDOC)
			(*red)->ambiguous = AMBIGUOUS;
		ft_lstadd_back_parser(parser_x, ft_lstnew_parser(NULL, NULL, *red));
		*red = NULL;
	}
}

static void	handle_filename(t_pars **pars, t_parser **parser_x,
		t_redirection **redirection)
{
	int	count;
	int	i;

	count = 0;
	count = count_node(*pars, FILENAME);
	(*redirection)->file = malloc(sizeof(char *) * (count + 1));
	if ((*redirection)->file == NULL)
		return ;
	i = 0;
	while (i < count)
	{
		(*redirection)->file[i] = ft_strdup((*pars)->content);
		*pars = (*pars)->next;
		i++;
	}
	(*redirection)->file[count] = NULL;
	ft_lstadd_back_parser(parser_x, ft_lstnew_parser(NULL, NULL, *redirection));
	*redirection = NULL;
}

void	parsing(t_pars *pars, t_parser **parser_x, t_command *command,
		t_redirection *redirection)
{
	while (pars)
	{
		if (pars->type == COMMAND)
			handle_command(pars, parser_x, &command);
		else if (pars->type == ARGUMENT)
		{
			handle_argument(&pars, parser_x, &command);
			continue ;
		}
		else if (pars->type == REDIRECT_IN || pars->type == REDIRECT_OUT
			|| pars->type == APPEND_OUT || pars->type == HEREDOC
			|| pars->type == R_IN_AMB || pars->type == R_OUT_AMB
			|| pars->type == A_OUT_AMB)
			handle_redir(pars, parser_x, &redirection);
		else if (pars->type == FILENAME)
		{
			handle_filename(&pars, parser_x, &redirection);
			continue ;
		}
		else if (pars->type == PIPE)
			ft_lstadd_back_parser(parser_x, ft_lstnew_parser(NULL,
					pars->content, NULL));
		if (pars)
			pars = pars->next;
	}
}
