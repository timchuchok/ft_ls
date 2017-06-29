/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_permissions_link.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 14:13:17 by vtymchen          #+#    #+#             */
/*   Updated: 2017/06/22 14:13:20 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_type(t_file *file)
{
	if ((S_ISBLK(file->mode)))
		ft_printf("b");
	else if ((S_ISCHR(file->mode)))
		ft_printf("c");
	else if ((S_ISDIR(file->mode)))
		ft_printf("d");
	else if ((S_ISLNK(file->mode)))
		ft_printf("l");
	else if ((S_ISSOCK(file->mode)))
		ft_printf("s");
	else if ((S_ISFIFO(file->mode)))
		ft_printf("p");
	else
		ft_printf("-");
}

void		print_attr_acl(t_file *file)
{
	acl_t		acl;
	acl_entry_t	dummy;
	ssize_t		xattr;
	char		c;

	acl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(file->path, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		c = '@';
	else if (acl != NULL)
		c = '+';
	else
		c = ' ';
	ft_printf("%c ", c);
}

static void	rwx(t_file *file)
{
	ft_printf((file->mode & S_IRUSR) ? "r" : "-");
	ft_printf((file->mode & S_IWUSR) ? "w" : "-");
	if (file->mode & S_ISUID)
	{
		ft_printf((file->mode & S_IEXEC) ? "s" : "");
		ft_printf((!(file->mode & S_IEXEC)) ? "S" : "");
	}
	else
		ft_printf((file->mode & S_IXUSR) ? "x" : "-");
	ft_printf((file->mode & S_IRGRP) ? "r" : "-");
	ft_printf((file->mode & S_IWGRP) ? "w" : "-");
	if (file->mode & S_ISGID)
	{
		ft_printf((file->mode & S_IEXEC) ? "s" : "");
		ft_printf((!(file->mode & S_IEXEC)) ? "S" : "");
	}
	else
		ft_printf((file->mode & S_IXGRP) ? "x" : "-");
	ft_printf((file->mode & S_IROTH) ? "r" : "-");
	ft_printf((file->mode & S_IWOTH) ? "w" : "-");
	if (file->mode & S_ISVTX)
		ft_printf("t");
	else
		ft_printf((file->mode & S_IXOTH) ? "x" : "-");
}

void		print_permissions(t_file *file)
{
	print_type(file);
	rwx(file);
	print_attr_acl(file);
}

void		print_link(t_file *file)
{
	char	*link_name;

	if (S_ISLNK(file->mode))
	{
		link_name = ft_strnew(4096);
		link_name[readlink(file->path, link_name, 4096)] = '\0';
		ft_printf(" -> %s", link_name);
		free(link_name);
	}
}
