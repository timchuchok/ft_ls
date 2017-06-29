/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 16:37:28 by vtymchen          #+#    #+#             */
/*   Updated: 2017/06/22 16:37:32 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	process_dir(t_list *dir_list, t_flags *flags)
{
	t_file *file;

	while (dir_list->content)
	{
		file = (t_file *)dir_list->content;
		rec_dir(file->name, flags);
		dir_list = dir_list->next;
	}
}

void	process_args(t_list *list, t_flags *flags)
{
	t_file	*file;
	t_list	*file_list;
	t_list	*dir_list;

	file_list = ft_lstnew(0, 0);
	dir_list = ft_lstnew(0, 0);
	while (list->content)
	{
		file = (t_file *)list->content;
		if ((S_ISREG(file->mode) || S_ISLNK(file->mode)) && !file->no_file)
			new_file(file->name, "", &file_list, flags);
		else if (S_ISDIR(file->mode) && !file->no_file)
			new_file(file->name, "", &dir_list, flags);
		list = list->next;
	}
	flags->sort_func(&file_list, flags);
	flags->sort_func(&dir_list, flags);
	flags->print_func(file_list, flags);
	flags->blocks = 0;
	process_dir(dir_list, flags);
	free_list(dir_list);
	free_list(file_list);
}

void	rec_dir(char *path, t_flags *flags)
{
	DIR				*d;
	struct dirent	*dirent1;
	t_list			*list;

	list = ft_lstnew(0, 0);
	if (!(d = opendir(path)))
	{
		print_error(path);
		free(list);
		return ;
	}
	while ((dirent1 = readdir(d)))
		new_file(dirent1->d_name, path, &list, flags);
	closedir(d);
	flags->sort_func(&list, flags);
	if (flags->output)
		ft_printf("\n%s:\n", path);
	flags->output = 1;
	if (flags->l)
		ft_printf("total %ld\n", flags->blocks);
	flags->print_func(list, flags);
	flags->blocks = 0;
	if (flags->rr)
		recurs(list, flags, path);
	free_list(list);
}

void	recurs(t_list *list, t_flags *flags, char *path)
{
	t_file	*file;
	char	*new_path;

	while (list->content)
	{
		file = (t_file *)list->content;
		if (S_ISDIR(file->mode) && !ft_strequ(file->name, ".") && \
								!ft_strequ(file->name, ".."))
		{
			new_path = ft_strjoin(ft_strdup(path), "/");
			new_path = ft_strjoin(new_path, file->name);
			if ((flags->a && file->name[0] == '.') || (file->name[0] != '.'))
				rec_dir(new_path, flags);
			free(new_path);
		}
		list = list->next;
	}
}
