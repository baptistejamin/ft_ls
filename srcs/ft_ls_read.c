/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:32:37 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/14 15:03:00 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <stdio.h>

t_file	*ft_ls_init_file(t_ls *ls, int level, char *name, char *path)
{
	t_file *file;

	file = (t_file *)malloc(sizeof(t_file));
	file->files = NULL;
	file->ls = ls;
	file->level = level;
	file->name = name;
	file->path = path;
	file->exists = (stat(path, &file->stat) == -1) ? 0 : 1;
	file->dir = opendir(path);
	file->type = file->stat.st_mode & S_IFMT;
	file->has_permission = 1;
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
	if (file->ls->options.is_recursive == 1)
		return (1);
	return (0);
}

void	ft_ls_read(t_ls *ls, t_list **list, char *name, char *path, int level, int should_walk)
{
	char						*new_path;
	struct dirent		*dirent;
	t_file					*file;
	t_list					*new;

	file = ft_ls_init_file(ls, level, name, path);
	//printf("ft_ls_read: %s\n", file->name);
	while (file->type == IS_DIR && file->dir && ft_can_walk(file) &&
		(dirent = readdir(file->dir)) != NULL)
	{
		new_path = ft_strnew(1);
		new_path = ft_strjoin(path, "/");
		new_path = ft_strfjoin(new_path, dirent->d_name);
		ft_ls_read(ls, &(file->files), dirent->d_name, new_path, level + 1, should_walk);
	}
	if (file->dir == NULL && file->type == IS_DIR)
		file->has_permission = 0;
	if (file->dir)
		closedir(file->dir);
	ft_ls_sort(ls, &(file->files));
	new = ft_lstnew(file, sizeof(t_file));
	ft_lstadd(list, new);
	if (!should_walk || (file->type == IS_DIR && ft_can_walk(file)))
		ft_simple_show(new);
}

void	ft_ls_parse_files(t_ls *ls, int ac, char **av)
{
	int			i;
	t_file	*file;
	t_list	*new;

	new = NULL;
	i = ls->args_start_index;
	ls->n_files = ac - i;
	if (ls->n_files == 0)
	{
		ls->n_files = 1;
		file = ft_ls_init_file(ls, 0, ".", ".");
		new = ft_lstnew(file, sizeof(t_file));
		ft_lstadd(&(ls->folders), new);
		return ;
	}
	while (i < ac)
	{
		if (ft_strcmp(av[i], "--") == 0)
			file = ft_ls_init_file(ls, 0, ".", ".");
		else
			file = ft_ls_init_file(ls, 0, av[i], av[i]);
		new = ft_lstnew(file, sizeof(t_file));
		if (file->type == IS_DIR)
			ft_lstadd(&(ls->folders), new);
		else
			ft_lstadd(&(ls->non_folders), new);
		i++;
	}
}
