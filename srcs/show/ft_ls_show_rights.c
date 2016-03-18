/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_show_rights.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:50:32 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/16 15:38:48 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_ls_show_right_execution(t_file *file, int mode_a,
									int mode_b, char *def)
{
	if (!(file->stat.st_mode & mode_a) && (file->stat.st_mode & mode_b))
		ft_putchar(def[0]);
	else if ((file->stat.st_mode & mode_a) && (file->stat.st_mode & mode_b))
		ft_putchar(def[1]);
	else
		ft_putchar((file->stat.st_mode & mode_a) ? def[2] : def[3]);
}

void	ft_ls_show_rights(t_file *file)
{
	ft_putstr(file->type == IS_DIR ? "d" : "");
	ft_putstr(file->type == IS_FIFO ? "p" : "");
	ft_putstr(file->type == IS_CHAR ? "c" : "");
	ft_putstr(file->type == IS_BLOCK ? "b" : "");
	ft_putstr(file->type == IS_FILE ? "-" : "");
	ft_putstr(file->type == IS_LINK ? "l" : "");
	ft_putstr(file->type == IS_SOCK ? "s" : "");
	ft_putchar((file->stat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((file->stat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_ls_show_right_execution(file, S_IXUSR, S_ISUID, "Ssx-");
	ft_putchar((file->stat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((file->stat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_ls_show_right_execution(file, S_IXGRP, S_ISGID, "Ssx-");
	ft_putchar((file->stat.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((file->stat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_ls_show_right_execution(file, S_IXOTH, S_ISVTX, "Ttx-");
	ft_putstr("  ");
}
