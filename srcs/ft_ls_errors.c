/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:50:32 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/16 15:38:48 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_ls_errors_wrong_option(char option)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(option, 2);
	ft_putchar_fd('\n', 2);
	ft_ls_errors_usage();
	exit(1);
}

void	ft_ls_errors_no_exists(t_file *file)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(file->name, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	ft_ls_errors_no_permission(t_file *file)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(file->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(file->err), 2);
}

void	ft_ls_errors_usage(void)
{
	ft_putstr_fd("usage: ft_ls [-Ralrt] [file ...]", 2);
	ft_putchar_fd('\n', 2);
}
