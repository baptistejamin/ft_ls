/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:24:29 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/12 21:38:19 by bjamin           ###   ########.fr       */
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

typedef struct	s_ls_options {
	int						is_full_show;
	int						is_recursive;
	int						is_all_files;
	int						is_reverse;
	int						is_ordered_by_time;
}								t_ls_options;

typedef struct	s_ls {
	t_ls_options	options;
	int						args_start_index;
	t_list				*files;
	int						n_files;
}								t_ls;

enum	e_type {
	IS_FILE = S_IFREG,
	IS_DIR = S_IFDIR,
	IS_CHAR = S_IFCHR,
	IS_BLOCK = S_IFBLK,
	IS_FIFO = S_IFIFO,
	IS_LINK = S_IFLNK,
	IS_SOCK = S_IFSOCK
};

typedef struct	s_file {
	int						level;
	char					*name;
	char					*path;
	int						exists;
	struct stat		stat;
	enum e_type		type;
	DIR						*dir;
	t_list				*files;
	t_ls					*ls;
}								t_file;

void						ft_ls_parse_files(t_ls *ls, int ac, char **av);
void						ft_ls_init_options(t_ls *ls);
void						ft_ls_parse_options(t_ls *ls, int ac, char **av);
void						ft_ls_debug_options(t_ls *ls);
void						ft_ls_errors_wrong_option(char option);
void						ft_ls_errors_usage();
void						ft_ls_sort(t_ls *ls, t_list **list);
void						ft_simple_show(t_list *elem);
void						*get_name(t_list *elem);
int							cmp_asc(void *a, void *b);



#endif