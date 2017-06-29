/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 10:05:00 by vtymchen          #+#    #+#             */
/*   Updated: 2017/06/15 10:05:03 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define ASCII(x, n, n2) x == 0 ? ft_strcmp(n, n2) > 0 : ft_strcmp(n, n2) < 0
#define TIME(x, t1, t2) x == 0 ? t1 < t2 : t1 > t2

void	sort_ascii(t_list **list, t_flags *flags)
{
	t_list	*curr;
	t_list	*next;
	void	*tmp;
	t_file	*file1;
	t_file	*file2;

	curr = *list;
	while (curr->content)
	{
		next = *list;
		while (next->next->content)
		{
			file1 = (t_file *)next->content;
			file2 = (t_file *)next->next->content;
			if (ASCII(flags->r, file1->name, file2->name))
			{
				tmp = next->content;
				next->content = next->next->content;
				next->next->content = tmp;
			}
			next = next->next;
		}
		curr = curr->next;
	}
}

void	sort_time(t_list **list, t_flags *flags)
{
	t_list	*curr;
	t_list	*next;
	void	*tmp;
	t_file	*file1;
	t_file	*file2;

	curr = *list;
	while (curr->content)
	{
		next = *list;
		while (next->next->content)
		{
			file1 = (t_file *)next->content;
			file2 = (t_file *)next->next->content;
			if (TIME(flags->r, file1->last_mod.tv_sec, file2->last_mod.tv_sec))
			{
				tmp = next->content;
				next->content = next->next->content;
				next->next->content = tmp;
			}
			next = next->next;
		}
		curr = curr->next;
	}
}

void	no_sort(t_list **list, t_flags *flags)
{
	if (flags && list)
		;
}
