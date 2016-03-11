/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:24:29 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/11 18:42:43 by bjamin           ###   ########.fr       */
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
	int						is_resursive;
	int						is_all_files;
	int						is_reverse;
	int						is_ordered_by_time;
}								t_ls_options;

typedef struct	s_ls {
	t_ls_options	options;
	int 					args_start_index;
	t_list 				*files;
}								t_ls;

typedef struct	s_type {
	int						is_file;
	int						is_dir;
	int						is_char;
	int						is_block;
	int						is_fifo;
	int						is_link;
	int						is_sock;
}								t_type;

typedef struct	s_file {
	int 					level;
	char					*name;
	char					*path_name;
	int 					exists;
	struct 				stat stat;
	t_type 				type;
	DIR 					*dir;
	t_list 				*files;
}								t_file;

void						ft_ls_read(t_ls *ls, int ac, char **av);
void 						ft_ls_init_options(t_ls *ls);
void 						ft_ls_parse_options(t_ls *ls, int ac, char **av);
void 						ft_ls_debug_options(t_ls *ls);
void 						ft_ls_errors_wrong_option(char option);
void 						ft_ls_errors_usage();

#endif