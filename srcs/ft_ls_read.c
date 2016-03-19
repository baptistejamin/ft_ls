/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:32:37 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/18 16:24:07 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_ls_assert_symlimks(t_file *file)
{
	file->lname = NULL;
	if (file->ls->follow && file->type == IS_LINK
		&& !file->ls->options.is_full_show
		&& !file->ls->options.is_ordered_by_time)
	{
		file->exists = (stat(file->path, &file->stat) != -1);
		if (!file->exists)
			file->exists = (lstat(file->path, &file->stat) != -1);
		else
			file->type = file->stat.st_mode & S_IFMT;
	}
	if (file->type == IS_LINK)
	{
		file->lname = ft_strnew(257);
		readlink(file->path, file->lname, 256);
	}
}

t_file	*ft_ls_init_file(t_ls *ls, int is_first_level, char *name, char *path)
{
	t_file *file;

	file = (t_file *)malloc(sizeof(t_file));
	file->files = NULL;
	file->ls = ls;
	file->first_level = is_first_level;
	file->name = name;
	file->path = path;
	file->exists = (lstat(path, &file->stat) != -1);
	file->type = 0;
	file->type = file->stat.st_mode & S_IFMT;
	ft_ls_assert_symlimks(file);
	file->owner = (getpwuid(file->stat.st_uid)) ?
		ft_strdup(getpwuid(file->stat.st_uid)->pw_name) :
		ft_itoa(file->stat.st_uid);
	file->group = (getgrgid(file->stat.st_gid)) ?
		ft_strdup(getgrgid(file->stat.st_gid)->gr_name) :
		ft_itoa(file->stat.st_gid);
	file->has_permission = 1;
	file->major = (file->type == IS_CHAR || file->type == IS_BLOCK) ?
		(int)MAJOR(file->stat.st_rdev) : 0;
	file->minor = (file->type == IS_CHAR || file->type == IS_BLOCK) ?
		(int)MINOR(file->stat.st_rdev) : 0;
	return (file);
}

void	ft_ls_read_dir(t_list *elem)
{
	t_dirent	*dirent;
	t_file		*new_file;
	t_file		*file;

	file = elem->content;
	file->dir = opendir(file->path);
	if (file->type == IS_DIR && file->dir == NULL)
		file->has_permission = 0;
	while (file->type == IS_DIR && file->dir && ft_can_walk(file) &&
		((dirent = readdir(file->dir)) != NULL))
	{
		if (dirent->d_name[0] != '.' || file->ls->options.is_all_files)
		{
			new_file = ft_ls_init_file(file->ls, 0, ft_strdup(dirent->d_name),
				ft_strfjoin(ft_strjoin(file->path, "/"), dirent->d_name));
			ft_lstadd(&(file->files), ft_lstnew(new_file, sizeof(t_file)));
			if (new_file)
				free(new_file);
			new_file = NULL;
		}
	}
	file->err = (file->type == IS_DIR && file->dir == NULL) ? errno : 0;
	if (file->dir)
		closedir(file->dir);
	ft_ls_sort(file->ls, &(file->files));
}

void	ft_ls_parse_files_free(t_file **file)
{
	if (*file)
		free(*file);
	*file = NULL;
}

void	ft_ls_parse_files(t_ls *ls, int ac, char **av)
{
	int		i;
	t_file	*file;

	i = ls->args_start_index;
	ls->n_files = ac - i;
	if (ls->n_files == 0)
	{
		ls->n_files = 1;
		file = ft_ls_init_file(ls, 1, ft_strdup("."), ft_strdup("."));
		ft_lstadd(&(ls->folders), ft_lstnew(file, sizeof(t_file)));
		ft_ls_parse_files_free(&file);
		return ;
	}
	while (i < ac)
	{
		file = ft_ls_init_file(ls, 1, ft_strdup(av[i]), ft_strdup(av[i]));
		if (!file->exists)
			ft_lstadd(&(ls->errors), ft_lstnew(file, sizeof(t_file)));
		else if (file->type == IS_DIR)
			ft_lstadd(&(ls->folders), ft_lstnew(file, sizeof(t_file)));
		else
			ft_lstadd(&(ls->non_folders), ft_lstnew(file, sizeof(t_file)));
		i++;
		ft_ls_parse_files_free(&file);
	}
}
