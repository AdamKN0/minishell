/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:57:50 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/17 14:58:32 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_access_in(t_in *in)
{
	while (in)
	{
		if (access(in->input, F_OK) == -1)
		{
			my_perror(in->input, "No such file or directory", 1, 1);
			return (0);
		}
		else if (access(in->input, R_OK) == -1)
		{
			my_perror(in->input, "Permission denied", 1, 1);
			return (0);
		}
		in = in->next;
	}
	return (1);
}

int	check_access_out(t_out *out)
{
	while (out)
	{
		if (access(out->output, F_OK) == -1)
		{
			my_perror(out->output, "No such file or directory", 1, 1);
			return (0);
		}
		else if (access(out->output, W_OK) == -1)
		{
			my_perror(out->output, "Permission denied", 1, 1);
			return (0);
		}
		out = out->next;
	}
	return (1);
}
