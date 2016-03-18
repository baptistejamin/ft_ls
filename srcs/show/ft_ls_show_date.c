/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_show_date.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:50:32 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/16 15:38:48 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_ls_show_date(t_list *elem)
{
	char	*str;
	time_t	now;
	t_file	*file;

	file = elem->content;
	now = time(0);
	str = ctime(get_time(elem));
	if (*((time_t *)get_time(elem)) > now ||
		(now - MONTH(6)) > *((time_t *)get_time(elem)))
	{
		write(1, ft_strsub(str, 4, 6), 3);
		ft_putstr(" ");
		write(1, ft_strsub(str, 8, 2), 2);
		ft_putstr("  ");
		write(1, ft_strsub(str, 20, 4), 4);
	}
	else
	{
		write(1, ft_strsub(str, 4, 3), 3);
		ft_putchar(' ');
		write(1, ft_strsub(str, 8, 2), 2);
		ft_putchar(' ');
		write(1, ft_strsub(str, 11, 5), 5);
	}
	ft_putstr(" ");
}
