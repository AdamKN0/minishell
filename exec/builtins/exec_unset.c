/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:55:45 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/16 17:45:19 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_env_var(t_env **env, t_cmd *cmd, int i)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->before_equal, cmd->cmd[i],
				ft_strlen(cmd->cmd[i])) == 0
			&& ft_strlen(cmd->cmd[i]) == ft_strlen(tmp->before_equal))
		{
			if (prev == NULL)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->before_equal);
			free(tmp->after_equal);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	exec_unset(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 1;
	while (cmd->cmd[i] != NULL)
	{
		if (check_isvalid(cmd->cmd[i]) == 1)
			ft_nonvalid("unset", cmd->cmd[i], "not a valid identifier");
		else
			remove_env_var(env, cmd, i);
		i++;
	}
}
