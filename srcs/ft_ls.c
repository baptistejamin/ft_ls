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
	ls->errors = NULL;
	ls->non_folders = NULL;
	ls->folders = NULL;
	ls->n_files = 1;
	ls->follow = 1;
	ls->first_processed = 0;
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

int	ft_can_walk(t_file *file)
{
	if (file->first_level == 1 && (ft_strcmp(file->name, ".") == 0 ||
		ft_strcmp(file->name, "..") == 0))
		return (1);
	if (!file->first_level && (ft_strcmp(file->name, ".") == 0 ||
		ft_strcmp(file->name, "..") == 0))
		return (0);
	if (file->first_level == 1)
		return (1);
	if (file->ls->options.is_recursive == 1)
		return (1);
	return (0);
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
	if (ls.non_folders && ls.options.is_all_files)
		get_max_values(ls.non_folders);
	ft_ls_process_files(ls.non_folders, 0);
	ft_ls_process_files(ls.folders, 1);
	return (0);
}
