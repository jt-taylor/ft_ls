/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_functions_ls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:31:22 by jtaylor           #+#    #+#             */
/*   Updated: 2019/07/08 12:57:47 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_dir_info(t_dir_info *t)
{
	ft_printf("\n\tPrinting t_dir_info :\n");
	ft_printf("name = %s\nclose = %i\ntotal = %u\nhead-name = %s\nlast-name = %s\ns_name = %u\ns_group = %u\ns_size = %u\ns_link = %u\n\n\n",
			t->name, (int)t->close, (unsigned int)t->total, t->head->name_file, t->last_file->name_file,
			(unsigned int)t->s_name,
			(unsigned int)t->s_group,
			(unsigned int)t->s_size,
			(unsigned int)t->s_link);
}

