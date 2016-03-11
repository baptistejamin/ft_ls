/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 13:17:16 by bjamin            #+#    #+#             */
/*   Updated: 2016/02/23 14:21:38 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strcut_base(char *str, char c)
{
	size_t	len;
	char	*ret;

	len = 0;
	ret = ft_strdup(str);
	while (ret[len] && ret[len] != c)
	{
		len++;
	}
	ret[len] = 0;
	return (ret);
}

int		ft_strcut(char **s1, char **s2, char c)
{
	char *tmp;

	*s1 = ft_strcut_base(*s2, c);
	tmp = ft_strsub(*s2, ft_strlen(*s1) + 1, ft_strlen(*s2) - ft_strlen(*s1));
	if (s2 && *s2)
		free(*s2);
	*s2 = ft_strdup(tmp);
	if (tmp)
		free(tmp);
	return (1);
}
