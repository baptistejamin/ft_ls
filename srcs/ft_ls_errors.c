/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:50:32 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/11 17:23:32 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_ls_errors_wrong_option(char option)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 1);
	ft_putchar_fd(option, 1);
	ft_putchar_fd('\n', 1);
	ft_ls_errors_usage();
	exit(1);
}

void	ft_ls_errors_usage(void)
{
	ft_putstr_fd("usage: ft_ls [-Ralrt] [file ...]", 1);
	ft_putchar_fd('\n', 1);
}
