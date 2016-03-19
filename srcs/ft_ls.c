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

int		ft_ls_init_env(t_ls *ls)
{
	ls->non_folders = NULL;
	ls->folders = NULL;
	ls->n_files = 1;
	ls->follow = 1;
	return (1);
}

void	ft_ls_process_files(t_list *list, int is_folder)
{
	t_list	*cur;

	cur = list;
	while (cur)
	{
		if (is_folder)
			ft_ls_show_dir(cur);
		else
			ft_ls_show_file(cur);
		cur = cur->next;
	}
	if (list)
		ft_lstdel(&list, &ft_ls_free_file);
}

int		main(int ac, char **av)
{
	t_ls	ls;

	ft_ls_init_env(&ls);
	ft_ls_init_options(&ls);
	ft_ls_parse_options(&ls, ac, av);
	ft_ls_parse_files(&ls, ac, av);
	ft_lstsort(&(ls.errors), &cmp_asc, &get_name);
	ft_ls_sort(&ls, &ls.non_folders);
	ft_ls_sort(&ls, &ls.folders);
	ft_ls_process_files(ls.errors, 0);
	get_max_values(ls.non_folders);
	ft_ls_process_files(ls.non_folders, 0);
	ft_ls_process_files(ls.folders, 1);
	return (0);
}
