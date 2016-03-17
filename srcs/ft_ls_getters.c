#include <ft_ls.h>
#include <stdio.h>

void  *get_name(t_list *elem)
{
	t_file *file;

	file = elem->content;
	return (file->name);
}

void  *get_time(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (file->ls->options.time_last_access)
		return (&file->stat.st_atime);
	else if (file->ls->options.time_creation)
		return (&file->stat.st_ctime);
	return (&file->stat.st_mtime);
}

int  get_nlink_size(t_list *elem)
{
	t_file *file;

	file = elem->content;
	return (ft_strlen(ft_itoa(file->stat.st_nlink)));
}

int get_group_size(t_list *elem)
{
	t_file *file;

	file = elem->content;
	return (ft_strlen(file->group));
}

int  get_owner_size(t_list *elem)
{
	t_file *file;

	file = elem->content;
	return (ft_strlen(file->owner));
}

int  get_minor_size(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (file->type == IS_CHAR || file->type == IS_BLOCK)
		return (ft_strlen(ft_itoa(file->minor)));
	return (0);
}

int  get_major_size(t_list *elem)
{
	t_file *file;

	file = elem->content;

	if (file->type == IS_CHAR || file->type == IS_BLOCK)
		return (ft_strlen(ft_itoa(file->major)));
	return (0);
}

int  get_size(t_list *elem)
{
	t_file *file;

	file = elem->content;
	if (file->type != IS_CHAR && file->type != IS_BLOCK)
		return (ft_strlen(ft_itoa(file->stat.st_size)));
	return (0);
}
