/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
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

int		main(int ac, char **av)
{
	t_ls	ls;
	t_file	*file;
	t_list *cur;

	ft_ls_init_env(&ls);
	ft_ls_init_options(&ls);
	ft_ls_parse_options(&ls, ac, av);
	ft_ls_parse_files(&ls, ac, av);
	ft_lstsort(&(ls.errors), &cmp_asc, &get_name);
	ft_lstsort(&(ls.non_folders), &cmp_asc, &get_name);
	ft_lstsort(&(ls.folders), &cmp_asc, &get_name);
	cur = ls.errors;
	while (cur)
	{
		ft_show_file(cur);
		cur = cur->next;
	}
	cur = ls.non_folders;
	get_max_values(ls.non_folders);
	while (cur)
	{
		ft_show_file(cur);
		cur = cur->next;
	}
	cur = ls.folders;
	while (cur)
	{
		file = (t_file *)cur->content;
		ft_show_dir(cur);
		cur = cur->next;
	}
	return (0);
}
