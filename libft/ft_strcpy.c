/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:24:02 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:24:02 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	*ft_cmemcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	i = 0;
	d = dest;
	s = src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen != 0 && dst)
	{
		ft_cmemcpy(dst, src, srclen);
		dst[srclen] = '\0';
	}
	return (srclen);
}
