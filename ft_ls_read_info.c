/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_read_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:11:34 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/05 14:43:09 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** so basically we are calling lstat and copyin all of the data into
** 		our info struct
** this is kind of a roundabout way of doing it but should make printing easier
*/

void		ft_ls_read_info(t_ft_ls *ls, char *argv)
{
	t_ft_ls_info		*info_file;
	int					num;

	num = lstat(argv, &ls->stat);
	file = //new_file(ls->files);
	file->name_file = ft_strdup(argv);
	if (num < 0)
		file->fail_file = 1;
	else
		//read_file_info(ls, ls->files, file);
	ft_bzero(&ls->stat, sizeof(ls->stat));
}
