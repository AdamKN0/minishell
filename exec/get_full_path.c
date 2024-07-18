/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:40:31 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/15 15:51:38 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->before_equal, "PATH", 4) == 0)
			return (env->after_equal);
		env = env->next;
	}
	return (NULL);
}

char	*get_full_path(char *cmd, t_env *env)
{
	char	*path;
	char	**dirs;
	char	*full_path;
	int		i;

	path = ft_getenv(env);
	dirs = ft_split(path, ':');
	full_path = NULL;
	i = 0;
	while (dirs && dirs[i] != NULL)
	{
		if (cmd[0] != '\0')
			full_path = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(full_path, &cmd[0]);
		if (!full_path)
			ft_error("failed to allocate memory", 1, 0);
		if ((access(full_path, X_OK)) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	if (!full_path && access(cmd, F_OK) == 0)
		full_path = ft_strdup(cmd);
	return (free(path), free(dirs), full_path);
}
