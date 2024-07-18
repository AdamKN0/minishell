/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:08:56 by kadam             #+#    #+#             */
/*   Updated: 2024/07/17 15:38:31 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_quotes(t_lexer *x_lexer)
{
	int	inside_single;
	int	inside_double;

	inside_single = 0;
	inside_double = 0;
	while (x_lexer != NULL)
	{
		if (x_lexer->type == DOUBLE_QUOTE && !inside_single)
			inside_double = !inside_double;
		else if (x_lexer->type == SINGLE_QUOTE && !inside_double)
			inside_single = !inside_single;
		x_lexer = x_lexer->next;
	}
	if (inside_single || inside_double)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching\n",
			2);
		return (0);
	}
	return (1);
}

int	check_pipe(t_lexer *ptr, t_lexer *prev, t_lexer *next)
{
	prev = ptr->prev;
	while (prev != NULL && prev->type == SPACE_X)
		prev = prev->prev;
	next = ptr->next;
	while (next != NULL && next->type == SPACE_X)
		next = next->next;
	if (prev == NULL || next == NULL || prev->type == PIPE
		|| next->type == PIPE)
		return (0);
	if (prev->type == REDIRECT_OUT && prev != NULL && prev != ptr->prev)
		return (0);
	if (prev && (prev->type == REDIRECT_IN || prev->type == APPEND_OUT
			|| prev->type == HEREDOC))
		return (0);
	return (1);
}

int	check_redirection(t_lexer *ptr, t_lexer *next, int *z)
{
	next = ptr->next;
	while (next != NULL && next->type == SPACE_X)
		next = next->next;
	if (next == NULL)
		return (0);
	if ((next->type == HEREDOC || next->type == APPEND_OUT
			|| next->type == REDIRECT_OUT || next->type == REDIRECT_IN)
		&& next->quote == NO_QUOTE)
	{
		if (next->type == HEREDOC)
			*z = 1;
		else if (next->type == APPEND_OUT)
			*z = 2;
		else if (next->type == REDIRECT_OUT)
			*z = 3;
		else if (next->type == REDIRECT_IN)
			*z = 4;
		return (0);
	}
	return (1);
}

int	check_is_error(char **message, int *i, t_lexer *ptr, int zz)
{
	t_nor1	nor;
	int		oo;

	nor.i = i;
	nor.x = 0;
	nor.y = 0;
	oo = 0;
	if (!check_quotes(ptr))
		return (0);
	while (ptr != NULL)
	{
		validate_heredoc(ptr, &nor.x, &nor.y);
		zz = check_and_validate_pipe(&ptr, nor, message);
		if (zz == 1)
			return (1);
		else if (zz == 0)
			return (0);
		oo = check_and_validate_redirection(&ptr, nor, message);
		if (oo == 1)
			return (1);
		else if (oo == 0)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}
