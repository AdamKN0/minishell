/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:15:29 by kadam             #+#    #+#             */
/*   Updated: 2024/07/10 20:30:13 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	x;

	i = 0;
	x = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == x)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == x)
		return ((char *)s + i);
	return (NULL);
}
