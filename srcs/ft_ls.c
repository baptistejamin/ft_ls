/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/12 19:59:11 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <stdio.h>

int		ft_ls_init_env(t_ls *ls)
{
	ls->files = NULL;
	ls->n_files = 1;
	return (1);
}

void	show_total(int total)
{
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putstr("\n");
}

int		get_total(t_list *elem)
{
	t_file	*file;
	int			total;

	total = 0;
	while (elem)
	{
		file = elem->content;
		elem = elem->next;
		total += file->stat.st_blocks;
	}
	return (total);
}

int		main(int ac, char **av)
{
	t_ls	ls;

	ft_ls_init_env(&ls);
	ft_ls_init_options(&ls);
	ft_ls_parse_options(&ls, ac, av);
	//ft_ls_debug_options(&ls);
	ft_ls_read(&ls, ac, av);
	return (0);
}
