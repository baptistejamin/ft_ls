/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:24:29 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/18 17:34:20 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <libft.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <unistd.h>
# include <errno.h>

# define MONTH(m)	((m) * 30 * 24 * 60 * 60)
# define MAJOR(m)	((__int32_t)(((__uint32_t)(m)) >> 24) & 0xff)
# define MINOR(m)	((__int32_t)((m) & 0xffffff))

typedef struct		s_ls_options
{
	int				is_raw;
	int				is_full_show;
	int				is_recursive;
	int				is_all_files;
	int				is_reverse;
	int				is_ordered_by_time;
	int				time_last_access;
	int				time_creation;
	int				skip_group;
}					t_ls_options;

typedef struct		s_ls
{
	t_ls_options	options;
	int				args_start_index;
	int				first_processed;
	t_list			*non_folders;
	t_list			*folders;
	t_list			*errors;
	int				n_files;
	int				follow;
}					t_ls;

enum	e_type
{
	IS_FILE = S_IFREG,
	IS_DIR = S_IFDIR,
	IS_CHAR = S_IFCHR,
	IS_BLOCK = S_IFBLK,
	IS_FIFO = S_IFIFO,
	IS_LINK = S_IFLNK,
	IS_SOCK = S_IFSOCK
};

typedef struct		s_file_sizes
{
	int				nlink_spaces;
	int				group_spaces;
	int				owner_spaces;
	int				date_spaces;
	int				size_spaces;
	int				major_spaces;
	int				minor_spaces;
	long long		total;
}					t_file_sizes;

typedef struct stat	t_stat;

typedef struct		s_file
{
	int				first_level;
	char			*name;
	char			*lname;
	char			*path;
	char			*owner;
	char			*group;
	int				exists;
	int				err;
	int				has_permission;
	t_stat			stat;
	t_file_sizes	sizes;
	enum e_type		type;
	DIR				*dir;
	t_list			*files;
	t_ls			*ls;
	int				minor;
	int				major;
}					t_file;

typedef struct dirent	t_dirent;

void				ft_ls_parse_files(t_ls *ls, int ac, char **av);
void				ft_ls_init_options(t_ls *ls);
void				ft_ls_parse_options(t_ls *ls, int ac, char **av);
void				ft_ls_errors_wrong_option(char option);
void				ft_ls_errors_usage();
void				ft_ls_errors_no_exists(t_file *file);
void				ft_ls_errors_no_permission(t_file *file);
void				ft_ls_read_dir(t_list *elem);
void				ft_ls_sort(t_ls *ls, t_list **list);
void				ft_ls_show_dir(t_list *elem);
void				ft_ls_show_rights(t_file *file);
void				ft_ls_show_file(t_list *elem);
void				ft_ls_show_int(int value, int max_space);
void				ft_ls_show_str(char *str, int max_space);
void				ft_ls_show_date(t_list *elem);
void				ft_ls_show_size(t_file *file);
int					ft_can_walk(t_file *file);
void				ft_ls_free_file(void *content, size_t content_size);
void				get_max_values(t_list *elem);
int					get_max_value(t_list *elem, int (f)(t_list *e));
void				get_max_nlink(t_list *elem);
void				get_max_group(t_list *elem);
void				get_max_owner(t_list *elem);
void				get_max_size(t_list *elem);
int					get_minor_size(t_list *elem);
int					get_major_size(t_list *elem);
int					get_size(t_list *elem);
long long			get_total(t_list *elem);
void				*get_name(t_list *elem);
void				*get_time(t_list *elem);
void				*get_time_nano(t_list *elem);
void				*get_elem(t_list *elem);
int					get_nlink_size(t_list *elem);
int					get_group_size(t_list *elem);
int					get_owner_size(t_list *elem);
int					cmp_asc(void *a, void *b);
int					no_dot_file(t_list *elem);

#endif
