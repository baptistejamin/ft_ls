/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:13:52 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/12 21:20:26 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_ls_init_options(t_ls *ls)
{
	ls->options.is_full_show = 0;
	ls->options.is_recursive = 0;
	ls->options.is_all_files = 0;
	ls->options.is_reverse = 0;
	ls->options.is_ordered_by_time = 0;
	ls->options.time_creation = 0;
	ls->options.time_last_access = 0;
	ls->options.is_raw = 0;
	ls->options.skip_group = 0;
}

int		ft_ls_options_is_in(char *str, char c)
{
	while (str && *str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int		ft_ls_parse_options_helper(t_ls *ls, char option)
{
	ls->options.is_raw = (option == '1') ? 1 : ls->options.is_raw;
	ls->options.is_full_show = (option == 'l') ? 1 : ls->options.is_full_show;
	ls->options.is_recursive = (option == 'R') ? 1 : ls->options.is_recursive;
	ls->options.is_all_files = (option == 'a') ? 1 : ls->options.is_all_files;
	ls->options.is_reverse = (option == 'r') ? 1 : ls->options.is_reverse;
	ls->options.is_ordered_by_time = (option == 't') ? 1 :
		ls->options.is_ordered_by_time;
	if (option == 'g')
	{
		ls->options.is_full_show = 1;
		ls->options.skip_group = 1;
	}
	if (option == 'u')
	{
		ls->options.time_creation = 0;
		ls->options.time_last_access = 1;
	}
	if (option == 'U')
	{
		ls->options.time_last_access = 0;
		ls->options.time_creation = 1;
	}
	return (ft_ls_options_is_in("RUaglrtu1", option));
}

void	ft_ls_parse_options(t_ls *ls, int ac, char **av)
{
	int i;
	int n;

	i = 1;
	ls->args_start_index = 1;
	while ((i < ac) && av[i][0] == '-' && ft_strcmp(av[i], "-") != 0)
	{
		n = 1;
		if (ft_strcmp(av[i], "--") == 0)
		{
			ls->args_start_index++;
			return ;
		}
		while (av[i][n])
		{
			if (!ft_ls_parse_options_helper(ls, av[i][n]))
				ft_ls_errors_wrong_option(av[i][n]);
			n++;
		}
		i++;
		ls->args_start_index = i;
	}
}
