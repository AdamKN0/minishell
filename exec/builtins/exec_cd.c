/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:42:41 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/17 14:59:05 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->before_equal, key, ft_strlen(key)) == 0)
		{
			free(tmp->after_equal);
			tmp->after_equal = ft_strdup(value);
		}
		tmp = tmp->next;
	}
}

void	add_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->before_equal, key, ft_strlen(key)) == 0)
			return ;
		tmp = tmp->next;
	}
	lstadd_back_env(env, lstnew_env(key, value, 0));
}

void	*ft_get_home(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->before_equal, "HOME",
				ft_strlen(env->before_equal)) == 0)
			return (env->after_equal);
		env = env->next;
	}
	return (NULL);
}

void	exec_cd(t_cmd *cmd, int f, t_env *env)
{
	char	*path;
	char	*old_path;
	char	*tmp;

	path = cmd->cmd[1];
	old_path = getcwd(NULL, 0);
	add_env(&env, "OLDPWD", old_path);
	update_env(&env, "OLDPWD", old_path);
	if (path == NULL || ft_strncmp(path, "~", 1) == 0)
		path = ft_get_home(env);
	if (path == NULL)
		my_perror("cd", "HOME not set", 1, f);
	else if (chdir(path) != 0)
		post_error("cd", path, 1, f);
	tmp = getcwd(NULL, 0);
	update_env(&env, "PWD", tmp);
	free(tmp);
	free(old_path);
}
