/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:53:53 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/18 15:14:16 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_if_exist(t_env *env, char *key)
{
	int	i;

	i = 0;
	while (key[i] != '\0' && key[i] != '=')
		i++;
	while (env)
	{
		if (ft_strncmp(env->before_equal, key, ft_strlen(key)) == 0
			&& ft_strlen(env->before_equal) == ft_strlen(key))
			return (1);
		env = env->next;
	}
	return (0);
}

t_env_v	init_v(t_env_v *v, t_env *env)
{
	v->check = 1;
	v->tmp = NULL;
	v->key = NULL;
	v->value = NULL;
	v->i = 1;
	v->tmp = env;
	return (*v);
}

t_env_v	get_key_value(char *cmd, t_env_v *v)
{
	v->check = 1;
	v->j = 0;
	while (cmd[v->j] != '\0' && cmd[v->j] != '=')
		v->j++;
	v->key = ft_substr(cmd, 0, v->j);
	if (cmd[v->j] == '=')
	{
		v->value = ft_substr(cmd, v->j + 1, ft_strlen(cmd));
		v->check = 0;
	}
	return (*v);
}

void	if_itsnot_valid(t_env_v *v, char *cmd)
{
	ft_nonvalid("export", cmd, "not a valid identifier");
	g_status = 1;
	free(v->key);
	v->key = NULL;
	free(v->value);
	v->value = NULL;
}

void	exec_export(t_cmd *cmd, t_env **env)
{
	t_env_v	v;

	v = init_v(&v, *env);
	if (cmd->cmd[1] == NULL)
		return (print_env(*env));
	while (cmd->cmd[v.i] != NULL)
	{
		v = get_key_value(cmd->cmd[v.i], &v);
		if (check_isvalid(v.key) == 1)
			if_itsnot_valid(&v, cmd->cmd[v.i]);
		else if (v.key == NULL)
			print_env(*env);
		else
		{
			if (check_if_exist(*env, v.key) == 1 && v.value != NULL)
				update_env(env, v.key, v.value);
			else if (!check_if_exist(*env, v.key))
				lstadd_back_env(env, lstnew_env(v.key, v.value, v.check));
			free(v.key);
			v.key = NULL;
			free(v.value);
			v.value = NULL;
		}
		v.i++;
	}
}
