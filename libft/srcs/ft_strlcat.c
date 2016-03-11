/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:25:20 by bjamin            #+#    #+#             */
/*   Updated: 2015/11/27 18:17:35 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		return (size + src_len);
	while (*dst)
	{
		dst++;
		i++;
	}
	while (*src && i < size - 1)
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	*dst = '\0';
	return (dst_len + src_len);
}
