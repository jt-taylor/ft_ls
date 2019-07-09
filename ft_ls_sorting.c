/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sorting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:52:31 by jtaylor           #+#    #+#             */
/*   Updated: 2019/07/08 21:42:26 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** get the number of elemts in the t_file_info linked list
*/

static inline int		ft_list_elem_total(t_file_info *list)
{
	int		i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

/*
** swap the position of two elemnts in the list
*/

static inline void		swap_elem(t_file_info *a, t_file_info *b)
{
	(a->prev) ? a->prev->next = b : 0;
	(b->next) ? b->next->prev = a : 0;
	b->prev = a->prev;
	a->next = b->next;
	b->next = a;
	a->prev = b;
}

/*
** this is a really inneficiant sorting alg
** always makes the maximum number of checks as is checks {a & b
** , b & c, c & d, etc } * (number of elements in the list)
** merge sort would be much better and is often the prefference for linked list
*/

static inline void		sort_by_time(t_dir_info *dir, t_file_info *file)
{
	int	i;
	int	j;
	int	length;

	i = -1;
	length = ft_list_elem_total(dir->head);
	while (++i < length)
	{
		j = -1;
		file = dir->head;
		while (file->next && ++j < length)
		{
			if ((file->mtime < file->next->mtime) ||
					((file->mtime == file->next->mtime) &&
					(ft_strcmp(file->name_file, file->next->name_file) > 0)))
			{
				(&dir->head->size == &file->size) ? dir->head = file->next : 0;
				(&dir->last_file->size == &file->next->size) ?
					dir->last_file = file : 0;
				swap_elem(file, file->next);
			}
			(file->next) ? file = file->next : 0;
		}
	}
}

static inline void		sort_by_name(t_dir_info *dir, t_file_info *file)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	len = ft_list_elem_total(dir->head) - 1;
	while (++i < len)
	{
		j = -1;
		file = dir->head;
		while (file->next && ++j < len)
		{
			if (ft_strcmp(file->name_file, file->next->name_file) > 0)
			{
				(&dir->head->size == &file->size) ? dir->head = file->next : 0;
				(&dir->last_file->size == &file->next->size) ?
					dir->last_file = file : 0;
				swap_elem(file, file->next);
			}
			(file->next) ? file = file->next : 0;
		}
	}
}

void					ft_ls_sort_lists(t_ls *ls, t_dir_info *dir)
{
	if (ls->flag & FLAG_LO_T)
		sort_by_time(dir, dir->head);
	else
		sort_by_name(dir, dir->head);
}
