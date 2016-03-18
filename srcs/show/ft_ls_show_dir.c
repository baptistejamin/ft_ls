/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_show_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:50:32 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/16 15:38:48 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		no_dot_file(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (file->name[0] == '.')
		return (0);
	return (1);
}

void	ft_ls_show_dir_name(t_list *elem)
{
	t_file	*file;

	file = elem->content;
	if (!((file->ls->n_files == 1 && !file->ls->first_processed) ||
		(!file->first_level && !file->ls->options.is_recursive) ||
		(file->ls->options.is_all_files &&
		!file->files && file->has_permission)))
	{
		if (file->ls->first_processed)
			ft_putstr("\n");
		ft_putstr(file->path);
		ft_putstr(":\n");
		file->ls->first_processed = 1;
	}
	if (!file->has_permission && (file->files ||
		file->ls->options.is_recursive || file->first_level))
		ft_ls_errors_no_permission(file);
	if (file->files && file->ls->options.is_full_show)
	{
		ft_putstr("total ");
		ft_putnbr(file->sizes.total);
		ft_putstr("\n");
	}
}

void	ft_ls_show_dir(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (file->type != IS_DIR)
		return ;
	ft_ls_read_dir(elem);
	file->sizes.total = get_total(file->files);
	get_max_values(file->files);
	ft_ls_show_dir_name(elem);
	if (!file->ls->options.is_all_files)
		ft_lstiter_if(file->files, &ft_ls_show_file, &no_dot_file);
	else
		ft_lstiter(file->files, &ft_ls_show_file);
	if (file->ls->options.is_recursive && !file->ls->options.is_all_files)
		ft_lstiter_if(file->files, &ft_ls_show_dir, &no_dot_file);
	else
		ft_lstiter(file->files, &ft_ls_show_dir);
	if (file->files)
		ft_lstdel(&(file->files), &ft_ls_free_file);
}
