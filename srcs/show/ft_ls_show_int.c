/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_show_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:50:32 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/16 15:38:48 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_ls_show_int(int value, int max_space)
{
	int		spaces;
  int   len;
  char  *str;

  str = ft_itoa(value);
  len = ft_strlen(str);
  if (str)
    free(str);
	spaces = max_space - len;
	while (spaces-- > 0)
		ft_putchar(' ');
	ft_putnbr(value);
	ft_putstr(" ");
}
