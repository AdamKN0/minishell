/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_amb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:33:26 by kadam             #+#    #+#             */
/*   Updated: 2024/07/18 14:23:27 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_words(t_pars *tmp, char **join, int y)
{
	char	*old_join;
	int		i;

	while (tmp && tmp->type == WORD && tmp->space == NO_SPACE)
	{
		old_join = *join;
		*join = ft_strjoin(*join, tmp->content);
		free(old_join);
		tmp = tmp->next;
		y = 1;
	}
	if (*join != NULL && y == 1)
	{
		i = 0;
		while (ft_is_space((*join)[i]))
			i++;
		if ((*join)[i] == '\0')
		{
			if (*join)
				free(*join);
			*join = ft_strdup("\" \"");
		}
	}
}

static char	*join_dollar_env_variables(t_pars **next, int x)
{
	char	*join;
	char	*old_join;
	t_pars	*tmp;

	tmp = (*next)->prev;
	join = ft_strdup("");
	while (*next && (*next)->type == DOLLAR_ENV)
	{
		process_words(tmp, &join, 0);
		old_join = join;
		join = ft_strjoin(join, (*next)->content);
		free(old_join);
		if ((*next)->space == Y_SPACE)
		{
			x = 1;
			break ;
		}
		*next = (*next)->next;
	}
	if (x)
		*next = (*next)->next;
	else if (x == 0 && *next)
		process_words(*next, &join, 0);
	return (join);
}

static void	check_and_set_ambiguity(t_pars *par_tmp, char *join)
{
	char	**split;
	int		i;

	split = ft_split(join, ' ');
	i = 0;
	while (split[i])
		i++;
	if (i > 1 || join[0] == '\0')
	{
		if (par_tmp->type == REDIRECT_IN)
			par_tmp->type = R_IN_AMB;
		if (par_tmp->type == REDIRECT_OUT)
			par_tmp->type = R_OUT_AMB;
		else if (par_tmp->type == APPEND_OUT)
			par_tmp->type = A_OUT_AMB;
	}
	free_2d_array(split, 0);
	free(join);
}

void	handle_ambiguous_redirection(t_pars **parser)
{
	t_pars	*par_tmp;
	t_pars	*next;
	char	*join;

	par_tmp = *parser;
	next = NULL;
	while (par_tmp != NULL)
	{
		next = par_tmp->next;
		if (par_tmp->type == REDIRECT_IN || par_tmp->type == REDIRECT_OUT
			|| par_tmp->type == APPEND_OUT)
		{
			while (next != NULL && (next->type == WORD
					&& next->space == NO_SPACE))
				next = next->next;
			if (next != NULL && next->type == DOLLAR_ENV)
			{
				join = join_dollar_env_variables(&next, 0);
				if (next == NULL || (next != NULL && next->type != DOLLAR_ENV))
					check_and_set_ambiguity(par_tmp, join);
			}
		}
		par_tmp = next;
	}
}
