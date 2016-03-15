/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_show.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:32:37 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/12 21:06:40 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <stdio.h>

void	ft_show_file(t_list *elem)
{
	t_file *file;

	file = elem->content;
	file->ls->first_processed = 1;
	ft_putendl(file->name);
}

int	no_dot_file(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (file->name[0] == '.')
		return (0);
	return (1);
}

void	ft_show_dir(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (file->type != IS_DIR)
		return ;

	ft_ls_read_dir(elem);
	if (file->files)
	{
		if (file->ls->n_files > 1 || (file->level > 0 && file->ls->options.is_recursive))
		{
			if (file->ls->first_processed)
				ft_putstr("\n");
			ft_putstr(file->path);
			ft_putstr(":\n");
		}
	}
	if (!file->ls->options.is_all_files)
		ft_lstiter_if(file->files, &ft_show_file, &no_dot_file);
	else
		ft_lstiter(file->files, &ft_show_file);
	if (file->ls->options.is_recursive)
	{
		if (!file->ls->options.is_all_files)
			ft_lstiter_if(file->files, &ft_show_dir, &no_dot_file);
		else
			ft_lstiter(file->files, &ft_show_dir);
	}
}
