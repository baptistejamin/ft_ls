/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_getters_types.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:50:32 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/16 15:38:48 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	*get_name(t_list *elem)
{
	t_file *file;

	file = elem->content;
	return (file->name);
}

void	*get_time(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (file->ls->options.time_last_access)
		return (&file->stat.st_atime);
	else if (file->ls->options.time_creation)
		return (&file->stat.st_ctime);
	return (&file->stat.st_mtime);
}

int		get_size(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (file->type != IS_CHAR && file->type != IS_BLOCK)
		return (ft_strlen(ft_itoa(file->stat.st_size)));
	return (0);
}

int		no_dot_file(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (file->name[0] == '.')
		return (0);
	return (1);
}
