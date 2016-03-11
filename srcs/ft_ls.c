/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/11 18:51:25 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <stdio.h>

int		ft_ls_init_env(t_ls *ls)
{
	ls->files = NULL;
	return (1);
}

void	show(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (file->type.is_dir && ft_strcmp(file->name, ".") != 0 && 
		ft_strcmp(file->name, "..") != 0)
		printf("\n%s:\n", file->path_name);
	else
		printf("%s\n", file->name);
	if (file->files)
		ft_lstiter(file->files, &show);
}

int		main(int ac, char **av)
{
	t_ls	ls;

	ft_ls_init_env(&ls);
	ft_ls_init_options(&ls);
	ft_ls_parse_options(&ls, ac, av);
	ft_ls_debug_options(&ls);
	ft_ls_read(&ls, ac, av);
	ft_lstiter(ls.files, &show);
	return (0);
}
