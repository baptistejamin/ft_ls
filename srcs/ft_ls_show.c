/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_show.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:32:37 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/16 16:01:25 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <stdio.h>

void	ft_show_file(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (!file->exists)
		return (ft_ls_errors_no_exists(file));
	file->ls->first_processed = 1;
	if (!file->ls->options.is_full_show)
		ft_putendl(file->name);
	else
	{
		ft_show_rights(file);
		ft_show_int(file->stat.st_nlink, file->sizes.nlink_spaces);
		ft_show_str(file->owner, file->sizes.owner_spaces);
		if (!file->ls->options.skip_group)
			ft_show_str(file->group, file->sizes.group_spaces);
		ft_show_size(file);
		ft_show_date(elem);
		ft_putstr(file->name);
		if (file->type == IS_LINK)
		{
			ft_putstr(" -> ");
			ft_putstr(file->lname);
		}
		ft_putstr("\n");
	}
}

void	ft_show_int(int value, int max_space)
{
	int		spaces;

	spaces = max_space - ft_strlen(ft_itoa(value));
	while (spaces-- > 0)
		ft_putchar(' ');
	ft_putnbr(value);
	ft_putstr(" ");
}

void	ft_show_str(char *str, int max_space)
{
	int		spaces;

	spaces = max_space - ft_strlen(str);
	ft_putstr(str);
	while (spaces-- > 0)
		ft_putchar(' ');
	ft_putstr("  ");
}

void  ft_show_right_execution(t_file *file, int mode_a, int mode_b, char *def)
{
	if (!(file->stat.st_mode & mode_a) && (file->stat.st_mode & mode_b))
		ft_putchar(def[0]);
	else if ((file->stat.st_mode & mode_a) && (file->stat.st_mode & mode_b))
		ft_putchar(def[1]);
	else
		ft_putchar((file->stat.st_mode & mode_a) ? def[2] : def[3]);
}

void	ft_show_rights(t_file *file)
{
	ft_putstr(file->type == IS_DIR ? "d" : "");
	ft_putstr(file->type == IS_FIFO ? "p" : "");
	ft_putstr(file->type == IS_CHAR ? "c" : "");
	ft_putstr(file->type == IS_BLOCK ? "b" : "");
	ft_putstr(file->type == IS_FILE ? "-" : "");
	ft_putstr(file->type == IS_LINK ? "l" : "");
	ft_putstr(file->type == IS_SOCK ? "s" : "");
	ft_putchar((file->stat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((file->stat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_show_right_execution(file, S_IXUSR, S_ISUID, "Ssx-");
	ft_putchar((file->stat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((file->stat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_show_right_execution(file, S_IXGRP, S_ISGID, "Ssx-");
	ft_putchar((file->stat.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((file->stat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_show_right_execution(file, S_IXOTH, S_ISVTX, "Ttx-");
	ft_putstr("  ");
}

void	ft_show_date(t_list *elem)
{
	char		*str;
	time_t	now;
	time_t  date;
	t_file *file;

	file = elem->content;
	now = time(0);
	date = *((time_t *)get_time(elem));
	str = ctime(&date);
	if (date > now || (now - MONTH(6)) > date)
	{
		write(1, ft_strsub(str, 4, 6), 3);
		ft_putstr(" ");
		write(1, ft_strsub(str, 8, 2), 2);
		ft_putstr(" ");
		//if (file->sizes.date_spaces)
		ft_putstr(" ");
		write(1, ft_strsub(str, 20, 4), 4);
	}
	else
	{
		write(1, ft_strsub(str, 4, 3), 3);
		ft_putchar(' ');
		write(1, ft_strsub(str, 8, 2), 2);
		ft_putchar(' ');
		write(1, ft_strsub(str, 11, 5), 5);
	}
	ft_putstr(" ");
}

void	ft_show_size(t_file *file)
{
	int	minor_spaces;
	int	major_spaces;

	minor_spaces = ft_strlen(ft_itoa(file->minor));
	major_spaces = ft_strlen(ft_itoa(file->major));

	if (file->type == IS_CHAR || file->type == IS_BLOCK)
	{
		ft_putchar(' ');
		while (major_spaces < file->sizes.major_spaces--)
			ft_putchar(' ');
		ft_putnbr(file->major);
		ft_putstr(", ");
		while (minor_spaces < file->sizes.minor_spaces--)
			ft_putchar(' ');
		ft_putnbr(file->minor);
		ft_putchar(' ');
	}
	else
	{
		if ((file->sizes.minor_spaces > 0 || file->sizes.major_spaces > 0))
			ft_show_int(file->stat.st_size, file->sizes.minor_spaces + file->sizes.major_spaces + 3);
		else
			ft_show_int(file->stat.st_size, file->sizes.size_spaces);
	}
}

void	ft_ls_show_dir_name(t_list *elem)
{
	t_file *file;
	int should_show;

	file = elem->content;
	should_show = 1;


	//TO show empty files on -R

	//printf("file->name %s, level %d\n", file->name, file->first_level);

	if (file->ls->n_files == 1 && !file->ls->first_processed)
		should_show = 0;
	if (!file->first_level && !file->ls->options.is_recursive)
		should_show = 0;
	if (file->ls->options.is_all_files && !file->files && file->has_permission)
		should_show = 0;

	//Si n_files == 1 && !file->ls->first_processed
	//	stop

	//Si m

	/*if (((!file->ls->options.is_recursive && file->files) || file->ls->options.is_recursive || !file->has_permission) &&
		(file->ls->n_files > 1 || (!file->ls->options.is_recursive) ||
		(!file->first_level && file->ls->options.is_recursive)))
		*/
	if (should_show)
	{
		if (file->ls->first_processed)
			ft_putstr("\n");
		ft_putstr(file->path);
		ft_putstr(":\n");
		//To check
		file->ls->first_processed = 1;
	}
	if (!file->has_permission && (file->files || file->ls->options.is_recursive || file->first_level))
		ft_ls_errors_no_permission(file);
	if (file->files && file->ls->options.is_full_show)
	{
		ft_putstr("total ");
		ft_putnbr(file->sizes.total);
		ft_putstr("\n");
	}
}

int		no_dot_file(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (file->name[0] == '.')
		return (0);
	return (1);
}

void	free_file(void *content, size_t content_size)
{
	t_file *file;

	file = content;
	if (file->name)
		free(file->name);
	if (file->path)
		free(file->path);
	if (file->owner)
		free(file->owner);
	if (file->group)
		free(file->group);
	if (file->type == IS_LINK)
		free(file->lname);
	content_size = 0;
}

void	ft_show_dir(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (file->type != IS_DIR)
		return ;
	ft_ls_read_dir(elem);
	file->sizes.total = get_total(file->files);
	get_max_values(file->files);
	ft_ls_show_dir_name(elem);
	if (!file->ls->options.is_all_files)
		ft_lstiter_if(file->files, &ft_show_file, &no_dot_file);
	else
		ft_lstiter(file->files, &ft_show_file);
	if (file->ls->options.is_recursive && !file->ls->options.is_all_files)
		ft_lstiter_if(file->files, &ft_show_dir, &no_dot_file);
	else
		ft_lstiter(file->files, &ft_show_dir);
	if (file->files)
		ft_lstdel(&(file->files), &free_file);
}
