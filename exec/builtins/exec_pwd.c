/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:55:18 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/17 14:58:56 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_pwd(t_cmd *cmd, int f)
{
	int		i;
	char	*path;

	(void)cmd;
	i = 0;
	path = NULL;
	path = getcwd(path, 0);
	if (path == NULL)
		post_error("pwd", "getcwd failed", 1, f);
	else
	{
		ft_putstr_fd(path, 1);
		write(1, "\n", 1);
		free(path);
	}
}
