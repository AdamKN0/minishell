/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:41 by kadam             #+#    #+#             */
/*   Updated: 2024/07/18 14:33:29 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_node_expand(t_lexer **lexer, t_lexer **lex_tmp,
		t_lexer *next, t_lexer *prev)
{
	t_lexer	*prev_copy;

	prev_copy = prev;
	while (prev_copy && prev_copy->type == SPACE_X)
		prev_copy = prev_copy->prev;
	if (prev_copy && (prev_copy->type == REDIRECT_IN
			|| prev_copy->type == REDIRECT_OUT || prev_copy->type == APPEND_OUT)
		&& (*lex_tmp)->quote != NO_QUOTE && (*lex_tmp)->inside != NO_INSIDE)
	{
		free((*lex_tmp)->content);
		(*lex_tmp)->content = ft_strdup("''");
		(*lex_tmp)->type = WORD;
		return ;
	}
	if (next != NULL)
		next->prev = prev;
	if (prev != NULL)
		prev->next = next;
	if (*lex_tmp == *lexer)
		*lexer = next;
	free((*lex_tmp)->content);
	free(*lex_tmp);
	*lex_tmp = next;
}

int	process_node_env(int *found, t_lexer **lex_tmp, t_env *env_tmp)
{
	int	i;

	i = 0;
	while (env_tmp->after_equal[i] != '\0'
		&& ft_is_space(env_tmp->after_equal[i]))
		i++;
	if (env_tmp->after_equal[i] == '\0' && (*lex_tmp)->prev
		&& (*lex_tmp)->prev->type == SPACE_X)
	{
		free((*lex_tmp)->content); 
		(*lex_tmp)->content = ft_strdup("");
		*found = 1;
		return (1);
	}
	else if ((*lex_tmp)->next && (*lex_tmp)->next->type != SPACE_X)
		return (0);
	else if ((*lex_tmp)->prev && (*lex_tmp)->prev->type == SPACE_X)
	{
		free((*lex_tmp)->content);
		(*lex_tmp)->content = ft_strtrim(env_tmp->after_equal, " \t\n\v\f\r");
		*found = 1;
		return (1);
	}
	return (0);
}

int	find_and_replace_content(t_lexer *lex_tmp, t_env **expander, int found)
{
	t_env	*env_tmp;

	env_tmp = *expander;
	while (env_tmp != NULL)
	{
		if (ft_strncmp(lex_tmp->content, env_tmp->before_equal,
				ft_strlen(env_tmp->before_equal)) == 0)
		{
			if (ft_strlen(env_tmp->before_equal) == ft_strlen(lex_tmp->content)
				&& env_tmp->after_equal && env_tmp->after_equal[0] != '\0')
			{
				if (process_node_env(&found, &lex_tmp, env_tmp) == 1)
					break ;
				return (free(lex_tmp->content),
					lex_tmp->content = ft_strdup(env_tmp->after_equal), 1);
			}
			else if (env_tmp->after_equal == NULL
				|| env_tmp->after_equal[0] == '\0')
				return (free(lex_tmp->content),
					lex_tmp->content = ft_strdup(""), 1);
		}
		env_tmp = env_tmp->next;
	}
	return (found);
}

static int	change_content_and_remove_node(t_lexer **lexer, t_lexer **lex_tmp,
		t_lexer *next, t_env **expander)
{
	int		found;
	char	*substr;
	t_lexer	*prev;

	substr = ft_substr((*lex_tmp)->content, 1, ft_strlen((*lex_tmp)->content)
			- 1);
	free((*lex_tmp)->content);
	(*lex_tmp)->content = substr;
	found = find_and_replace_content(*lex_tmp, expander, 0);
	prev = (*lex_tmp)->prev;
	if (found == 0)
		remove_node_expand(lexer, lex_tmp, next, prev);
	return (found);
}

void	change_node(t_lexer **lexer, t_env **expander)
{
	t_lexer	*lex_tmp;
	t_lexer	*next;

	lex_tmp = *lexer;
	next = NULL;
	while (lex_tmp != NULL)
	{
		next = lex_tmp->next;
		if (lex_tmp->type == DOLLAR_ENV && ((lex_tmp->quote == NO_QUOTE
					&& lex_tmp->inside == NO_INSIDE)
				|| (lex_tmp->quote == DOUBLE && lex_tmp->inside == NO_INSIDE)
				|| (lex_tmp->quote == SINGLE
					&& lex_tmp->inside == INSIDE_SINGLE)))
		{
			if (change_content_and_remove_node(lexer, &lex_tmp, next,
					expander) == 0)
				continue ;
		}
		lex_tmp = next;
	}
}
