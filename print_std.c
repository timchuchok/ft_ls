/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_std.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 13:54:29 by vtymchen          #+#    #+#             */
/*   Updated: 2017/06/29 09:23:20 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(const char *filename)
{
	ft_printf("ls: %s: ", filename);
	perror("");
}

void	print_usage(char c)
{
	ft_printf("ls: illegal option -- %c\n", c);
	ft_printf("usage: ls [-laRrtgGf]");
	ft_printf("[file ...]\n");
	exit(1);
}

void	print_no_files(t_list *list)
{
	t_file *file;

	while (list->content)
	{
		file = (t_file *)list->content;
		if (file->no_file)
			print_error(file->name);
		list = list->next;
	}
}

void	std_error(void)
{
	perror("Oops");
	exit(1);
}

void	free_list(t_list *list)
{
	t_file *f;
	t_list *l;

	while (list->content)
	{
		f = (t_file *)list->content;
		free(f->name);
		free(f->path);
		free(list->content);
		l = list;
		list = list->next;
		free(l);
	}
	free(list);
}
