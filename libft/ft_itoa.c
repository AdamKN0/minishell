/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 21:22:06 by kadam             #+#    #+#             */
/*   Updated: 2024/07/10 19:11:06 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_len(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	int		j;
	char	*dest;

	i = check_len(n);
	j = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	dest = (char *)malloc((i + 1) * (sizeof(char)));
	if (dest == NULL)
		return (NULL);
	dest[i] = '\0';
	if (n < 0)
	{
		dest[j++] = '-';
		n = -n;
	}
	i--;
	while (i >= j)
	{
		dest[i] = (n % 10) + '0';
		i--;
		n = n / 10;
	}
	return (dest);
}
