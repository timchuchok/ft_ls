/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 15:20:40 by vtymchen          #+#    #+#             */
/*   Updated: 2017/06/23 15:20:43 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			is_flag(const char *s)
{
	if (*s == '-' && ft_strlen(s) > 1)
		return (1);
	return (0);
}

static void			read_flag(const char *arg, t_flags *flags)
{
	int		i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'l')
			flags->l = 1;
		else if (arg[i] == 'R')
			flags->rr = 1;
		else if (arg[i] == 'a')
			flags->a = 1;
		else if (arg[i] == 'r')
			flags->r = 1;
		else if (arg[i] == 't')
			flags->t = 1;
		else if (arg[i] == 'G')
			flags->gg = 1;
		else if (arg[i] == 'g')
			flags->g = 1;
		else if (arg[i] == 'f')
			flags->f = 1;
		else
			print_usage(arg[i]);
		i++;
	}
}

static void			init_func(t_flags *flags)
{
	if (!flags->t)
		flags->sort_func = &sort_ascii;
	else
		flags->sort_func = &sort_time;
	if (!flags->l)
		flags->print_func = &print_def;
	else
		flags->print_func = &print_long;
	if (flags->f)
	{
		flags->a = 1;
		flags->sort_func = &no_sort;
	}
}

void				read_args(int ac, char **av, t_flags *flags, t_list **list)
{
	int		i;

	i = 1;
	while (i < ac && is_flag(av[i]))
	{
		read_flag(av[i], flags);
		i++;
	}
	while (i < ac)
	{
		new_file(av[i], "", list, flags);
		i++;
	}
	init_func(flags);
}
