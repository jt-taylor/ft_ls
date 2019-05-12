/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 13:32:51 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/11 23:15:53 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


/*
** sort by name and sort by time work the same just comparing (time / name)
**
** this goes through the list and swaps an element for the next one in the list
** 		, this is really inefecient but probably wont matter except on very
** 		large linked list such as recursively going through the entire NFS
** 	the better option would be to use merge sort for the double linked list
** 		but that adds more complexity as far as managing the splitting and
** 		merging of all of the partial linked lists
**
** 		the reason this sorting implementation is so slow is because we only
** 			ever compare adjacent elements in the list so things can only ever
** 			swap places with the element next to it and we have to move each
** 			element one by one instead of just jumping to wear it belongs
** 	tldr	this should be much slower than merge sort but i don't feel that
** 			the speed will be an issue , it's already gonna be slow with
** 			recursion anyway
*/

static inline int	ft_ls_strlen_list_elem(t_ft_ls_info *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

/*
** if a is not the first element , set the element befor 'a' that links to 'a'
** 		to link to 'b' instead;
** 	and the oposite for b and the next element;
**
** 	then swap the prev and next links for a and b;
*/

static inline void	ft_ls_swap_list_elem(t_ft_ls_info *a, t_ft_ls_info *b)
{
	(a->prev) ? a->prev->next = b : 0;
	(b->next) ? b->next->prev = a : 0;
	b->prev = a->prev;
	b->next = a;
	a->next = b->next;
	a->prev = b;
}

/*
** sort the list by the ->mtime value
*/

static inline void	ft_ls_sort_lists_bytime(t_ft_ls_dir *dir, t_ft_ls_info *tmp)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	len = ft_ls_strlen_list_elem(dir->head) - 1;
	while (++i < len)
	{
		j = -1;
		tmp = dir->head;
		while (tmp->next && ++j < len)
		{
			if ((tmp->mtime < tmp->next->mtime) ||
					((tmp->mtime == tmp->next->mtime) &&
					 (ft_strcmp(tmp->name_file, tmp->next->name_file) > 0)))
			{
				(&dir->head->size == &tmp->size) ? dir->head = tmp->next : 0;
				(&dir->last_file->size == &tmp->next->size) ?
					dir->last_file = tmp : 0;
				ft_ls_swap_list_elem(tmp, tmp->next);
			}
			if (tmp->next)
				tmp = tmp->next;
		}
	}
}

/*
**		sort the linked list by the ->name_file
*/

static inline void	ft_ls_sort_lists_byname(t_ft_ls_dir *dir, t_ft_ls_info *tmp)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	len = ft_ls_strlen_list_elem(dir->head) - 1;
	while (++i < len)
	{
		j = -1;
		tmp = dir->head;
		while (tmp->next && ++j < len)
		{
			if (ft_strcmp(tmp->name_file, tmp->next->name_file) > 0)
			{
				(&dir->head->size == &tmp->size) ? dir->head = tmp->next : 0;
				(&dir->last_file->size == &tmp->next->size)
				? dir->last_file = tmp : 0;
				ft_ls_swap_list_elem(tmp, tmp->next);
			}
			if (tmp->next)
				tmp = tmp->next;
		}
	}
}

/*
** do i really need to explain this function 
*/

void		ft_ls_sort_list_elem(t_ft_ls *ls, t_ft_ls_dir *dir)
{
	if (ls->flag & FLAG_T)
		ft_ls_sort_lists_bytime(dir, dir->head);
	else
		ft_ls_sort_lists_byname(dir, dir->head);
}
