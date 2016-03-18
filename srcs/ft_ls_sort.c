/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:32:37 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/16 13:45:45 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <stdio.h>

int		time_asc(void *a, void *b)
{
	time_t	*time_a;
	time_t	*time_b;
	long	*nano_a;
	long	*nano_b;

	time_a = get_time((t_list *)a);
	time_b = get_time((t_list *)b);
	nano_a = get_time_nano((t_list *)a);
	nano_b = get_time_nano((t_list *)b);
	if (*time_a == *time_b)
		return (*nano_a >= *nano_b);
	else
		return (*time_a > *time_b);
}

int		cmp_asc(void *a, void *b)
{
	return (ft_strcmp((char *)a, (char *)b) < 0);
}

void	ft_ls_sort(t_ls *ls, t_list **list)
{
	ft_lstsort(list, &cmp_asc, &get_name);
	if (ls->options.is_ordered_by_time)
		ft_lstsort(list, &time_asc, &get_elem);
	if (ls->options.is_reverse)
		ft_lstrev(list);
}
