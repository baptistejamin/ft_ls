/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_show_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:50:32 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/16 15:38:48 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_ls_show_size(t_file *file)
{
	int	minor_spaces;
	int	major_spaces;

	minor_spaces = ft_strlen(ft_itoa(file->minor));
	major_spaces = ft_strlen(ft_itoa(file->major));
	if (file->type == IS_CHAR || file->type == IS_BLOCK)
	{
		ft_putchar(' ');
		while (major_spaces < file->sizes.major_spaces--)
			ft_putchar(' ');
		ft_putnbr(file->major);
		ft_putstr(", ");
		while (minor_spaces < file->sizes.minor_spaces--)
			ft_putchar(' ');
		ft_putnbr(file->minor);
		ft_putchar(' ');
	}
	else
	{
		if ((file->sizes.minor_spaces > 0 || file->sizes.major_spaces > 0))
			ft_ls_show_int(file->stat.st_size,
				file->sizes.minor_spaces + file->sizes.major_spaces + 3);
		else
			ft_ls_show_int(file->stat.st_size, file->sizes.size_spaces);
	}
}
