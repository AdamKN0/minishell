/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:17:56 by kadam             #+#    #+#             */
/*   Updated: 2024/07/16 12:23:47 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*print_message(int i)
{
	if (i == 0)
		return ("minishell: syntax error near unexpected token `newline'\n");
	else if (i == 1)
		return ("minishell: syntax error near unexpected token `<<'\n");
	else if (i == 2)
		return ("minishell: syntax error near unexpected token `>>'\n");
	else if (i == 3)
		return ("minishell: syntax error near unexpected token `>'\n");
	else if (i == 4)
		return ("minishell: syntax error near unexpected token `<'\n");
	else if (i == 5)
		return ("minishell: syntax error near unexpected token `|'\n");
	else
		return (NULL);
}

void	validate_heredoc(t_lexer *ptr, int *x, int *y)
{
	if (ptr->type == HEREDOC && ptr->quote == NO_QUOTE
		&& ptr->inside == NO_INSIDE && ptr->next)
	{
		ptr = ptr->next;
		while (ptr != NULL && ptr->type == SPACE_X)
			ptr = ptr->next;
		if (ptr && ptr->quote == NO_QUOTE && ptr->inside == NO_INSIDE
			&& (ptr->type == PIPE || ptr->type == REDIRECT_OUT
				|| ptr->type == REDIRECT_IN || ptr->type == APPEND_OUT
				|| ptr->type == HEREDOC))
			*x = 1;
		else
		{
			(*y)++;
			*x = 2;
		}
	}
}

int	check_and_validate_redirection(t_lexer **ptr, t_nor1 nor, char **message)
{
	int	z;

	z = 0;
	if (((*ptr)->type == REDIRECT_OUT || (*ptr)->type == REDIRECT_IN
			|| (*ptr)->type == APPEND_OUT || (*ptr)->type == HEREDOC)
		&& (*ptr)->quote == NO_QUOTE)
	{
		if (check_redirection(*ptr, NULL, &z) == 0)
		{
			if (nor.x == 2)
			{
				if (z >= 0 && z <= 4)
					*message = ft_strdup(print_message(z));
				return (*(nor.i) = nor.y, 1);
			}
			else
			{
				if (z >= 0 && z <= 4)
					printf("%s", print_message(z));
				return (0);
			}
		}
	}
	return (2);
}

int	check_and_validate_pipe(t_lexer **ptr, t_nor1 nor, char **message)
{
	if ((*ptr)->type == PIPE && (*ptr)->quote == NO_QUOTE)
	{
		if (check_pipe(*ptr, NULL, NULL) == 0)
		{
			if (nor.x == 2)
			{
				*message = ft_strdup(print_message(5));
				*(nor.i) = nor.y;
				return (1);
			}
			else
			{
				printf("%s", print_message(5));
				return (0);
			}
		}
	}
	return (2);
}
