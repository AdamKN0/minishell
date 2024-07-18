/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:00:45 by kadam             #+#    #+#             */
/*   Updated: 2024/06/22 17:56:18 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_node(t_pars *pars, int type)
{
	int	count;

	count = 0;
	while (pars)
	{
		if (pars->type == (t_type)type)
			count++;
		else
			break ;
		pars = pars->next;
	}
	return (count);
}
