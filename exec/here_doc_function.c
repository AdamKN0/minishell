/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:54:03 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/16 12:03:38 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*__path(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->before_equal, "PATH",
				ft_strlen(env->before_equal)) == 0)
			return (env->after_equal);
		env = env->next;
	}
	return (NULL);
}

int	change_content(t_lexer **lex_tmp, t_env **expander)
{
	int		found;
	char	*substr;
	t_lexer	*prev;

	substr = ft_substr((*lex_tmp)->content, 1, ft_strlen((*lex_tmp)->content)
			- 1);
	free((*lex_tmp)->content);
	(*lex_tmp)->content = substr;
	found = find_and_replace_content(*lex_tmp, expander, 0);
	if (found == 1)
		(*lex_tmp)->type = WORD;
	prev = (*lex_tmp)->prev;
	return (found);
}

void	processtmp(int x, t_env *env, t_lexer *lexer_x)
{
	t_lexer	*tmp;

	tmp = lexer_x;
	if (x == 0)
	{
		while (tmp != NULL)
		{
			if (tmp->type == DOLLAR_ENV)
				change_content(&tmp, &env);
			tmp = tmp->next;
		}
	}
	else if (x == 1)
	{
		while (tmp != NULL)
		{
			if (tmp->type == EXIT_STATUS)
			{
				free(tmp->content);
				tmp->content = ft_strdup("$?");
				tmp->type = WORD;
			}
			tmp = tmp->next;
		}
	}
}
