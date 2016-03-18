/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:32:37 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/16 15:49:50 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <stdio.h>

t_file	*ft_ls_init_file(t_ls *ls, int is_first_level, char *name, char *path, int follow)
{
	t_file *file;

	file = (t_file *)malloc(sizeof(t_file));
	file->files = NULL;
	file->ls = ls;
	file->first_level = is_first_level;
	file->name = name;
	file->path = path;
	file->exists = (lstat(path, &file->stat) != -1);
	file->type = file->stat.st_mode & S_IFMT;
	if (follow && file->type == IS_LINK && !ls->options.is_full_show)
	{
		file->exists = (stat(path, &file->stat) != -1);
		if (!file->exists)
			file->exists = (lstat(path, &file->stat) != -1);
		else
			file->type = file->stat.st_mode & S_IFMT;
	}
	file->has_permission = 1;
	file->owner = getpwuid(file->stat.st_uid) ?
		ft_strjoin("", getpwuid(file->stat.st_uid)->pw_name) :
		ft_strjoin("", ft_itoa(file->stat.st_uid));
	file->group = getgrgid(file->stat.st_gid) ?
		ft_strjoin("", getgrgid(file->stat.st_gid)->gr_name) :
		ft_strjoin("", ft_itoa(file->stat.st_gid));
	file->major = (file->type == IS_CHAR || file->type == IS_BLOCK) ?
		(int)MAJOR(file->stat.st_rdev) : 0;
	file->minor = (file->type == IS_CHAR || file->type == IS_BLOCK) ?
		(int)MINOR(file->stat.st_rdev) : 0;
	if (file->type == IS_LINK)
	{
		file->lname = ft_strnew(257);
		readlink(file->path, file->lname, 256);
	}
	return (file);
}

int		ft_can_walk(t_file *file)
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

void	ft_ls_read_dir(t_list *elem)
{
	char						*new_path;
	char						*new_name;
	struct dirent		*dirent;
	t_file					*new_file;
	t_file					*file;
	t_list					*new;

	file = elem->content;
	file->dir = opendir(file->path);
	if (file->type == IS_DIR && file->dir == NULL)
		file->has_permission = 0;
	while (file->type == IS_DIR && file->dir && ft_can_walk(file) &&
		(dirent = readdir(file->dir)) != NULL)
	{
		new_path = ft_strnew(1);
		new_path = ft_strjoin(file->path, "/");
		new_path = ft_strfjoin(new_path, dirent->d_name);
		new_name = ft_strnew(ft_strlen(dirent->d_name));
		new_name = ft_strcpy(new_name, dirent->d_name);
		new_file = ft_ls_init_file(file->ls, 0, new_name, new_path, 0);
		new = ft_lstnew(new_file, sizeof(t_file));
		if (new_file->name[0] != '.' || file->ls->options.is_all_files)
			ft_lstadd(&(file->files), new);
	}
	if (file->type == IS_DIR && file->dir == NULL)
		file->err = errno;
	if (file->dir)
		closedir(file->dir);
	ft_ls_sort(file->ls, &(file->files));
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
		file = ft_ls_init_file(ls, 1, ".", ".", 1);
		new = ft_lstnew(file, sizeof(t_file));
		ft_lstadd(&(ls->folders), new);
		return ;
	}
	while (i < ac)
	{
		file = ft_ls_init_file(ls, 1, av[i], av[i], 1);
		new = ft_lstnew(file, sizeof(t_file));
		if (file->type == IS_DIR)
			ft_lstadd(&(ls->folders), new);
		else if (file->exists)
			ft_lstadd(&(ls->non_folders), new);
		else
			ft_lstadd(&(ls->errors), new);
		i++;
	}
}
