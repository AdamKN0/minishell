/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:50:50 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/16 17:46:30 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**env_variables(t_env *env)
{
	t_env	*tmp;
	char	**ret;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	ret[i] = NULL;
	i = 0;
	tmp = env;
	while (tmp)
	{
		ret[i] = ft_strjoin(tmp->before_equal, "=");
		ret[i] = ft_strjoin(ret[i], tmp->after_equal);
		i++;
		tmp = tmp->next;
	}
	return (ret);
}

void	print_env(t_env *env)
{
	while (env != NULL)
	{
		printf("declare -x ");
		printf("%s", env->before_equal);
		if (env->after_equal)
		{
			printf("=");
			printf("\"%s\"", env->after_equal);
		}
		printf("\n");
		env = env->next;
	}
}

void	exec_env(t_cmd *cmd, t_env *env, int f)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
		i++;
	if (i > 1)
		post_error("env", cmd->cmd[1], 1, f);
	else
	{
		while (env != NULL)
		{
			if (env->after_equal)
			{
				printf("%s=", env->before_equal);
				printf("%s\n", env->after_equal);
			}
			env = env->next;
		}
	}
}
