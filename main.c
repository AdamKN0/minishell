/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:31:49 by kadam             #+#    #+#             */
/*   Updated: 2024/07/16 16:32:49 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_norm2	norm2;

	(void)av;
	initiliaze_struct(&norm2);
	if (ac != 1)
		return (printf("Error: No arguments needed\n"), 1);
	handle_signals();
	expander(&norm2.expander_x, env);
	while (1)
	{
		if (ft_readline(&norm2.line, 0, 0) == 0)
			continue ;
		lexer_norm2_x(&norm2);
		if (check_is_error(&norm2.message, &norm2.i, norm2.lexer_x, 0) == 0)
		{
			clear_all(&norm2, 1, 1);
			continue ;
		}
		if (process_and_free_norm2(&norm2) == 1)
			continue ;
	}
	ft_lstclear_env(&norm2.expander_x);
	exit(g_status);
}
