/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/14 14:58:58 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <stdio.h>

int		ft_ls_init_env(t_ls *ls)
{
	ls->non_folders = NULL;
	ls->folders = NULL;
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
	t_file	*file;

	ft_ls_init_env(&ls);
	ft_ls_init_options(&ls);
	ft_ls_parse_options(&ls, ac, av);
	ft_ls_parse_files(&ls, ac, av);
	ft_lstsort(&(ls.non_folders), &cmp_asc, &get_name);
	ft_lstsort(&(ls.folders), &cmp_asc, &get_name);
	while (ls.non_folders)
	{
		file = (t_file *)ls.non_folders->content;
		ft_ls_read(&ls, &(ls.files), file->name, file->path, 0, 0);
		ls.non_folders = ls.non_folders->next;
	}
	while (ls.folders)
	{
		file = (t_file *)ls.folders->content;
		ft_ls_read(&ls, &(ls.files), file->name, file->path, 0, 1);
		ls.folders = ls.folders->next;
	}
	return (0);
}
