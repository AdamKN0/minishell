/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:44:01 by aaskal            #+#    #+#             */
/*   Updated: 2023/12/26 16:34:18 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*str2;

	if (dst == src)
		return (dst);
	i = 0;
	str = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	while (i < n)
	{
		str[i] = str2[i];
		i++;
	}
	return (dst);
}

// int	main(void)
// {
// 	char nn[] = ""
// 	char d[] = "";
// char s[] = "abc";
// 	ft_memcpy("d", "d", 10);
// 	printf("%s\n", ft_memcpy("d", "d", 10));
// }
