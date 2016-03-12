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

int		ft_can_show(t_file *file)
{
	if (file->level == 0 && ft_strcmp(file->name, ".") == 0)
		return (1);
	if (!file->ls->options.is_all_files && *(file->name) == '.')
		return (0);
	return (1);
}

void	ft_simple_show(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (!file->exists)
		return (ft_ls_errors_no_exists(file));
	if (file->type == IS_DIR && !file->has_permission)
		return (ft_ls_errors_no_permission(file));
	if (!ft_can_show(file))
		return ;
	if (file->type == IS_DIR && file->files)
	{
		if (file->ls->n_files > 1 || file->ls->options.is_recursive)
		{
			ft_putstr("\n");
			ft_putstr(file->path);
			ft_putstr(":\n");
		}
		ft_lstiter(file->files, &ft_simple_show);
	}
	else
		ft_putendl(file->name);
}
