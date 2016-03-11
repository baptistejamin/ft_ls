/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:32:37 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/11 19:37:38 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <stdio.h>

t_file	*ft_ls_init_file(int level)
{
	t_file *file;

	file = (t_file *)malloc(sizeof(t_file));
	file->files = NULL;
	file->level = level;
	return (file);
}

void		ft_ls_get_type(t_file *file)
{
	file->type.is_file = S_ISREG(file->stat.st_mode);
	file->type.is_dir = S_ISDIR(file->stat.st_mode);
	file->type.is_char = S_ISCHR(file->stat.st_mode);
	file->type.is_block = S_ISBLK(file->stat.st_mode);
	file->type.is_fifo = S_ISFIFO(file->stat.st_mode);
	file->type.is_link = S_ISLNK(file->stat.st_mode);
	file->type.is_sock = S_ISSOCK(file->stat.st_mode);
}

int 	__can_walk(t_ls *ls, t_file *file)
{
	if (file->level == 0 && (ft_strcmp(file->name, ".") == 0 || 
		ft_strcmp(file->name, "..") == 0))
		return (1);
	if (file->level > 0 && (ft_strcmp(file->name, ".") == 0 || 
		ft_strcmp(file->name, "..") == 0))
		return (0);
	if (file->level == 0)
		return (1);
	if (ls->options.is_resursive == 1)
		return (1);
	return (0);
}


void	*get_name(t_list *elem)
{
	t_file *file;
	file = elem->content;
	return (file->name);
}

int		cmp_asc(void *a, void *b)
{
	return (ft_strcmp((char *)a, (char *)b) < 0);
}

void 	sort_by_name(t_list **list)
{
	ft_lstsort(list, &cmp_asc, &get_name);
}

void	ft_ls_read_path(t_ls *ls, t_list **list, char *name, char *path_name, int level)
{
	t_file *file;
	t_list *new;
	char 	 *new_path;

	struct dirent *dirent;

	file = ft_ls_init_file(level);
	file->path_name = path_name;
	file->name = name;
	file->exists = (stat(path_name, &file->stat) == -1) ? 0 : 1;
	file->dir = opendir(path_name);
	ft_ls_get_type(file);
	if (file->type.is_dir && file->dir && __can_walk(ls, file))
	{
		while ((dirent = readdir(file->dir)) != NULL) {
			new_path = ft_strnew(1);
			new_path = ft_strjoin(path_name, "/");
			new_path = ft_strfjoin(new_path, dirent->d_name);
			ft_ls_read_path(ls, &(file->files), dirent->d_name, new_path, level + 1);
		}
	}
	new = ft_lstnew(file, sizeof(t_file));
	ft_lstadd(list, new);
	sort_by_name(list);
}

void	ft_ls_read(t_ls *ls, int ac, char **av)
{
	int i;

	i = ls->args_start_index;
	if (ac == 1)
		ft_ls_read_path(ls, &(ls->files), ".", ".", 0);
	while (i < ac)
	{
		if (ft_strcmp(av[i], "--") == 0)
			ft_ls_read_path(ls, &(ls->files), ".", ".", 0);
		else
			ft_ls_read_path(ls, &(ls->files), av[i], av[i], 0);
		i++;
	}
}
