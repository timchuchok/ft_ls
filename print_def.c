/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_def.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 15:20:31 by vtymchen          #+#    #+#             */
/*   Updated: 2017/06/23 15:20:33 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	procces_def(t_list *list, t_flags *flags, int *i, int cols)
{
	t_file	*file;

	file = (t_file *)list->content;
	if (flags->gg)
		print_color(file, flags);
	if (flags->a)
	{
		ft_printf("%-*s", flags->file_length + 2, file->name);
		(*i)++;
	}
	if (!flags->a)
		if (file->name[0] != '.')
		{
			ft_printf("%-*s", flags->file_length + 2, file->name);
			(*i)++;
		}
	ft_printf("\033[0m");
	flags->output = 1;
	if (*i == cols)
	{
		ft_printf("\n");
		*i = 0;
	}
}

void		print_def(t_list *list, t_flags *flags)
{
	struct winsize	ts;
	int				cols;
	int				i;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ts);
	if (flags->file_length)
		cols = ts.ws_col / (flags->file_length + 2) - 1;
	else
		cols = 1;
	i = 0;
	while (list->content)
	{
		procces_def(list, flags, &i, cols);
		list = list->next;
	}
	if (i)
		ft_printf("\n");
	flags->file_length = 0;
}
