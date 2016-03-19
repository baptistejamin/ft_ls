/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_getters_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:50:32 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/16 15:38:48 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int	get_nlink_size(t_list *elem)
{
	int		len;
	char	*str;
	t_file	*file;

	file = elem->content;
	str = ft_itoa(file->stat.st_nlink);
	len = ft_strlen(str);
	if (str)
		free(str);
	return (len);
}

int	get_group_size(t_list *elem)
{
	t_file *file;

	file = elem->content;
	return (ft_strlen(file->group));
}

int	get_owner_size(t_list *elem)
{
	t_file *file;

	file = elem->content;
	return (ft_strlen(file->owner));
}

int	get_minor_size(t_list *elem)
{
	int		len;
	char	*str;
	t_file	*file;

	file = elem->content;
	if (file->type == IS_CHAR || file->type == IS_BLOCK)
	{
		str = ft_itoa(file->minor);
		len = ft_strlen(str);
		if (str)
			free(str);
		return (len);
	}
	return (0);
}

int	get_major_size(t_list *elem)
{
	int		len;
	char	*str;
	t_file	*file;

	file = elem->content;
	if (file->type == IS_CHAR || file->type == IS_BLOCK)
	{
		str = ft_itoa(file->major);
		len = ft_strlen(str);
		if (str)
			free(str);
		return (len);
	}
	return (0);
}
