/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sizes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:32:37 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/16 13:45:45 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <stdio.h>

long long	get_total(t_list *elem)
{
	t_file		*file;
	long long	total;

	total = 0;
	while (elem)
	{
		file = elem->content;
		elem = elem->next;
		if (file->name[0] != '.' || file->ls->options.is_all_files)
			total += file->stat.st_blocks;
	}
	return (total);
}

void		get_max_values(t_list *elem)
{
	t_file	*file;
	t_list	*cur;

	cur = elem;
	while (cur)
	{
		file = cur->content;
		cur = cur->next;
		file->sizes.nlink_spaces = get_max_value(elem, &get_nlink_size);
		file->sizes.group_spaces = get_max_value(elem, &get_group_size);
		file->sizes.owner_spaces = get_max_value(elem, &get_owner_size);
		file->sizes.major_spaces = get_max_value(elem, &get_major_size);
		file->sizes.minor_spaces = get_max_value(elem, &get_minor_size);
		file->sizes.size_spaces = get_max_value(elem, &get_size);
	}
}

int			get_max_value(t_list *elem, int (f)(t_list *e))
{
	t_list	*cur;
	t_file	*file;
	int		spaces;
	int		max;

	max = 0;
	cur = elem;
	while (cur)
	{
		file = cur->content;
		if ((file->name[0] != '.' || file->ls->options.is_all_files))
		{
			spaces = f(cur);
			if (spaces > max)
				max = spaces;
		}
		cur = cur->next;
	}
	return (max);
}
