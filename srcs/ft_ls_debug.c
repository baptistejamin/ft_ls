/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 15:36:49 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/14 14:03:46 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_ls_debug_options(t_ls *ls)
{
	ft_putstr("##### ft_ls_debug_options #####\n");
	if (ls->options.is_full_show)
		ft_putstr("ls->options.is_full_show (-l)\n");
	if (ls->options.is_recursive)
		ft_putstr("ls->options.is_recursive (-R)\n");
	if (ls->options.is_all_files)
		ft_putstr("ls->options.is_all_files (-a)\n");
	if (ls->options.is_reverse)
		ft_putstr("ls->options.is_reverse (-r)\n");
	if (ls->options.is_ordered_by_time)
		ft_putstr("ls->options.is_ordered_by_time (-t)\n");
}
