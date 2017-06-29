/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 08:53:17 by vtymchen          #+#    #+#             */
/*   Updated: 2017/06/23 08:53:20 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	fill_length(t_file *file, struct stat info, t_flags *flags)
{
	struct passwd	*pwd;
	struct group	*gr;

	if ((flags->a && file->name[0] == '.') || file->name[0] != '.')
	{
		if ((int)ft_strlen(file->name) > flags->file_length)
			flags->file_length = (int)ft_strlen(file->name);
		pwd = getpwuid(file->uid);
		gr = getgrgid(file->gid);
		if ((int)ft_strlen(gr->gr_name) > flags->gid_length)
			flags->gid_length = (int)ft_strlen(gr->gr_name);
		if ((int)ft_strlen(pwd->pw_name) > flags->uid_length)
			flags->uid_length = (int)ft_strlen(pwd->pw_name);
		if (flags->size_length < nbr_length_base(file->size, 10))
			flags->size_length = nbr_length_base(file->size, 10);
		if (flags->link_length < nbr_length_base(file->link_nbr, 10))
			flags->link_length = nbr_length_base(file->link_nbr, 10);
		if ((flags->a && file->name[0] == '.') || file->name[0] != '.')
			flags->blocks += info.st_blocks;
		if (flags->minor_length < nbr_length_base(minor(file->rdev), 10))
			flags->minor_length = nbr_length_base(minor(file->rdev), 10);
		if (flags->major_length < nbr_length_base(major(file->rdev), 10))
			flags->major_length = nbr_length_base(major(file->rdev), 10);
	}
}

void		reset_length(t_flags *flags)
{
	flags->uid_length = 0;
	flags->gid_length = 0;
	flags->file_length = 0;
	flags->size_length = 0;
	flags->link_length = 0;
	flags->minor_length = 0;
	flags->major_length = 0;
}

static void	fill_info(t_file *file, struct stat info, t_flags *flags)
{
	file->mode = info.st_mode;
	file->link_nbr = info.st_nlink;
	file->uid = info.st_uid;
	file->gid = info.st_gid;
	file->size = info.st_size;
	file->rdev = info.st_rdev;
	file->last_mod = info.st_mtimespec;
	fill_length(file, info, flags);
}

void		new_file(char *name, char *path, t_list **list, t_flags *flags)
{
	t_file		*file;
	struct stat info;
	t_list		*elem;
	char		*full_path;

	if (!(file = (t_file *)malloc(sizeof(t_file))))
		std_error();
	ft_bzero(file, sizeof(t_file));
	file->name = ft_strdup(name);
	if (*path != '\0')
	{
		full_path = ft_strjoin(ft_strdup(path), "/");
		full_path = ft_strjoin(full_path, name);
	}
	else
		full_path = ft_strdup(name);
	if (lstat(full_path, &info))
		file->no_file = 1;
	else
		fill_info(file, info, flags);
	file->path = ft_strdup(full_path);
	elem = ft_lstnew(file, sizeof(t_file));
	free(full_path);
	free(file);
	ft_lstadd(list, elem);
}

int			main(int ac, char **av)
{
	t_list	*list;
	t_flags	*flags;

	list = ft_lstnew(0, 0);
	flags = (t_flags *)malloc(sizeof(t_flags));
	if (!flags)
		std_error();
	ft_bzero(flags, sizeof(t_flags));
	read_args(ac, av, flags, &list);
	if (!list->content)
		new_file(".", "", &list, flags);
	flags->sort_func(&list, flags);
	print_no_files(list);
	process_args(list, flags);
	return (0);
}
