/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:13:52 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/11 16:33:58 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_ls_init_options(t_ls *ls)
{
	ls->options.is_full_show = 0;
	ls->options.is_resursive = 0;
	ls->options.is_all_files = 0;
	ls->options.is_reverse = 0;
	ls->options.is_ordered_by_time = 0;
}

int		ft_ls_parse_options_helper(t_ls *ls, char option)
{
	if (option == 'l')
		ls->options.is_full_show = 1;
	else if (option == 'R')
		ls->options.is_resursive = 1;
	else if (option == 'a')
		ls->options.is_all_files = 1;
	else if (option == 'r')
		ls->options.is_reverse = 1;
	else if (option == 't')
		ls->options.is_ordered_by_time = 1;
	else
		return (0);
	return (1);
}

void	ft_ls_parse_options(t_ls *ls, int ac, char **av)
{
	int i;
	int n;

	i = 1;
	ls->args_start_index = i;
	while (i < ac)
	{
		n = 1;
		if (av[i][0] != '-' && av[i][1] != '-')
		{
			ls->args_start_index = i;
			return ;
		}
		while (av[i][0] == '-' && av[i][1] != '-' && av[i][n])
		{
			if (!ft_ls_parse_options_helper(ls, av[i][n]))
				ft_ls_errors_wrong_option(av[i][n]);
			n++;
		}
		i++;
	}
}
