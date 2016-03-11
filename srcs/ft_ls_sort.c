/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:32:37 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/11 19:37:38 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <stdio.h>

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
	return (&file->stat.st_mtime);
}


int		cmp_asc(void *a, void *b)
{
	return (ft_strcmp((char *)a, (char *)b) < 0);
}

int		time_asc(void *a, void *b)
{
	time_t time1;
	time_t time2;

	time1 = *(time_t*)a;
	time2 = *(time_t*)b;
	return (time1 > time2);
}

void	ft_ls_sort(t_ls *ls, t_list **list)
{
	if (ls->options.is_ordered_by_time)
		ft_lstsort(list, &time_asc, &get_time);
	else
		ft_lstsort(list, &cmp_asc, &get_name);
	if (ls->options.is_reverse)
		ft_lstrev(list);
}