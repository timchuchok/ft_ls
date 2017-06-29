/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 14:15:25 by vtymchen          #+#    #+#             */
/*   Updated: 2017/06/22 14:15:29 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_uid_gid_name(t_file *file, t_flags *flags)
{
	struct passwd	*pwd;
	struct group	*gr;

	if (!flags->g)
	{
		pwd = getpwuid(file->uid);
		ft_printf("%-*s", flags->uid_length + 2, pwd->pw_name);
	}
	gr = getgrgid(file->gid);
	ft_printf("%-*s", flags->gid_length + 2, gr->gr_name);
	if (S_ISCHR(file->mode) || S_ISBLK(file->mode))
	{
		ft_printf("%*d, ", flags->major_length, major(file->rdev));
		ft_printf("%*d", flags->minor_length, minor(file->rdev));
	}
	else
		ft_printf("%*d", flags->size_length, file->size);
}

static void	print_date(t_file *file)
{
	time_t	time1;
	time_t	cur_time;
	char	*str1;
	char	*str2;

	time(&cur_time);
	time1 = (time_t)file->last_mod.tv_sec;
	str1 = ft_strdup(ctime(&cur_time));
	str2 = ft_strdup(ctime(&time1));
	if (cur_time - time1 < 1)
	{
		ft_printf(" %.7s %.4s ", &str2[4], &str2[20]);
		return ;
	}
	if (!ft_strcmp(&str1[20], &str2[20]))
		ft_printf(" %.12s ", &str2[4]);
	else
		ft_printf(" %.7s %.4s ", &str2[4], &str2[20]);
	free(str1);
	free(str2);
}

void		print_color(t_file *file, t_flags *flags)
{
	if (flags->gg)
	{
		if (S_ISDIR(file->mode))
			ft_printf("\033[34;01m");
		else if (S_ISLNK(file->mode))
			ft_printf("\033[35;01m");
		else if (S_ISFIFO(file->mode))
			ft_printf("\033[33;01m");
		else if (file->mode & S_IEXEC)
			ft_printf("\033[31;01m");
		else if (S_ISCHR(file->mode))
			ft_printf("\033[34;43m");
		else if (S_ISBLK(file->mode))
			ft_printf("\033[34;46m");
	}
}

void		print_long(t_list *list, t_flags *flags)
{
	t_file	*file;

	while (list->content)
	{
		file = (t_file *)list->content;
		if ((flags->a && file->name[0] == '.') || (file->name[0] != '.'))
		{
			print_permissions(file);
			ft_printf("%*d ", flags->link_length, file->link_nbr);
			print_uid_gid_name(file, flags);
			print_date(file);
			print_color(file, flags);
			ft_printf("%-s", file->name);
			ft_printf("\033[0m");
			print_link(file);
			ft_printf("\n");
		}
		list = list->next;
		flags->output = 1;
	}
	reset_length(flags);
}
