/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:53 by kadam             #+#    #+#             */
/*   Updated: 2024/07/12 10:10:43 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**join_2d_array(char **array1, char **array2, int i, int j)
{
	char	**new_array;

	new_array = NULL;
	if (!array1)
		return (array2);
	if (!array2)
		return (array1);
	new_array = malloc(sizeof(char *) * (cout_2d_array(array1)
				+ cout_2d_array(array2) + 1));
	if (!new_array)
		return (NULL);
	while (array1[i])
		new_array[j++] = ft_strdup(array1[i++]);
	i = 0;
	while (array2[i])
		new_array[j++] = ft_strdup(array2[i++]);
	new_array[j] = NULL;
	free_2d_array(array2, 0);
	return (new_array);
}
