/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:06:59 by vtymchen          #+#    #+#             */
/*   Updated: 2017/06/09 11:07:01 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"

/*
** dirent.h for opendir, readdir, closedir
** sys/stat.h for stat, lstat, S_ISDIR ..
*/

# include <dirent.h>
# include <sys/stat.h>

/*
** pwd.h for getpwuid
** grp.h for getgrgid
** sys/xattr.h for listxattr(@)
** sys/acl.h for acl(+)
** sys/ioctl.h for terminal width
*/

# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>

typedef struct			s_file
{
	char				*name;
	char				no_file;
	mode_t				mode;
	nlink_t				link_nbr;
	uid_t				uid;
	gid_t				gid;
	off_t				size;
	dev_t				rdev;
	char				*path;
	struct timespec		last_mod;
	struct timespec		last_acces;
}						t_file;

typedef struct s_flags	t_flags;

struct					s_flags
{
	char				l;
	char				rr;
	char				a;
	char				r;
	char				t;
	char				gg;
	char				g;
	char				f;
	int					uid_length;
	int					gid_length;
	int					file_length;
	int					size_length;
	int					link_length;
	int					minor_length;
	int					major_length;
	blkcnt_t			blocks;
	int					output;
	void				(*sort_func)(t_list **, t_flags *);
	void				(*print_func)(t_list *, t_flags *);
};

void					read_args(int ac, char **av, t_flags *f, t_list **l);

void					reset_length(t_flags *flags);
void					new_file(char *n, char *p, t_list **l, t_flags *f);

void					print_error(const char *s);
void					print_usage(char c);
void					std_error(void);
void					print_no_files(t_list *list);
void					free_list(t_list *list);

void					sort_ascii(t_list **list, t_flags *flags);
void					sort_time(t_list **list, t_flags *flags);
void					no_sort(t_list **list, t_flags *flags);

void					print_def(t_list *list, t_flags *flags);
void					print_long(t_list *list, t_flags *flags);
void					print_color(t_file *file, t_flags *flags);

void					print_type(t_file *file);
void					print_attr_acl(t_file *file);
void					print_permissions(t_file *file);
void					print_link(t_file *file);

void					process_args(t_list *list, t_flags *flags);
void					rec_dir(char *path, t_flags *flags);
void					recurs(t_list *list, t_flags *flags, char *path);

#endif
