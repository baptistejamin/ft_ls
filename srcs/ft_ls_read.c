/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:32:37 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/12 20:53:53 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <stdio.h>

t_file	*ft_ls_init_file(t_ls *ls, int level)
{
	t_file *file;

	file = (t_file *)malloc(sizeof(t_file));
	file->files = NULL;
	file->ls = ls;
	file->level = level;
	return (file);
}

int		ft_can_walk(t_file *file)
{
	if (file->level == 0 && (ft_strcmp(file->name, ".") == 0 ||
		ft_strcmp(file->name, "..") == 0))
		return (1);
	if (file->level > 0 && (ft_strcmp(file->name, ".") == 0 ||
		ft_strcmp(file->name, "..") == 0))
		return (0);
	if (file->level == 0)
		return (1);
	if (file->ls->options.is_resursive == 1)
		return (1);
	return (0);
}

int		ft_can_show(t_file *file)
{
	if (file->level == 0 && ft_strcmp(file->name, ".") == 0)
		return (1);
	if (!file->ls->options.is_all_files && *(file->name) == '.')
		return (0);
	return (1);
}

void	simple_show(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (!ft_can_show(file))
		return ;
	if (file->type == IS_DIR && file->files)
	{
		if (file->ls->n_files > 1)
		{
			ft_putstr("\n");
			ft_putstr(file->path_name);
			ft_putstr(":\n");
		}
		ft_lstiter(file->files, &simple_show);
	}
	else
		ft_putendl(file->name);
}

void	ft_ls_read_path(t_ls *ls, t_list **list, char *name, char *path_name, int level)
{
	t_file				*file;
	t_list				*new;
	char					*new_path;
	struct dirent	*dirent;

	file = ft_ls_init_file(ls, level);
	file->path_name = path_name;
	file->name = name;
	file->exists = (stat(path_name, &file->stat) == -1) ? 0 : 1;
	file->dir = opendir(path_name);
	file->type = file->stat.st_mode & S_IFMT;
	if (file->type == IS_DIR && file->dir && ft_can_walk(file))
	{
		while ((dirent = readdir(file->dir)) != NULL)
		{
			new_path = ft_strnew(1);
			new_path = ft_strjoin(path_name, "/");
			new_path = ft_strfjoin(new_path, dirent->d_name);
			ft_ls_read_path(ls, &(file->files), dirent->d_name, new_path, level + 1);
		}
	}
	if (file->dir)
		closedir(file->dir);
	ft_ls_sort(ls, &(file->files));
	new = ft_lstnew(file, sizeof(t_file));
	ft_lstadd(list, new);
	if (file->type == IS_DIR && ft_can_walk(file))
	{
		simple_show(new);
	}
}

void	ft_ls_read(t_ls *ls, int ac, char **av)
{
	int i;

	i = ls->args_start_index;
	if (ac == 1)
		ft_ls_read_path(ls, &(ls->files), ".", ".", 0);
	ls->n_files = ac - i;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "--") == 0)
			ft_ls_read_path(ls, &(ls->files), ".", ".", 0);
		else
			ft_ls_read_path(ls, &(ls->files), av[i], av[i], 0);
		i++;
	}
}
