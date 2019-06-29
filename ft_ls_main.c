/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 14:53:55 by jtaylor           #+#    #+#             */
/*   Updated: 2019/06/27 16:22:03 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	ft_usage(char c)
{
	ft_dprintf(2, "ft_ls: illegal option -- %c\nusage ft_ls [-larRt] [file]\n",
			c);
	exit(1);
}

/*
** for each arg starting with '-'
** check the flags //
** stored in a unsigned char
*/

static int	ft_ls_check_flags(t_ls *ls, char **argv, int ac)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (++i && argv[i][0] && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] == 'l')
				ls->flag |= FLAG_LO_L;
			else if (argv[i][j] == 'a')
				ls->flag |= FLAG_LO_A;
			else if (argv[i][j] == 'R')
				ls->flag |= FLAG_UP_R;
			else if (argv[i][j] == 'r')
				ls->flag |= FLAG_LO_R;
			else if (argv[i][j] == 't')
				ls->flag |= FLAG_LO_T;
			else
				ft_usage(argv[i][j]);
			j++;
		}
		if (i == ac - 1)
			break ;
	}
	return (i + 1);
}

/*
** if args check flags
** if args other than options read each 'file' and sort the dir
** otherwise act on '.' dir
**
** then the fun part is last
** printing everything
*/

int		main(int ac, char **argv)
{
	t_ls	*ls;
	int		i;

	i = 0;
	ls = (t_ls *)malloc(sizeof(t_ls));
	ft_bzero(ls, sizeof(t_ls));
	ls->files = (t_dir_info *)malloc(sizeof(t_dir_info));
	ft_bzero(ls->files, sizeof(t_dir_info));
	if (ac > 1 && argv[1][0] == '-' && argv[1][1])
		i = ft_ls_check_flags(ls, argv, ac);
	if ((ac > 1 && i < ac && !ls->flag && ++i) || (ac > i && ls->flag))
	{
		while (i < ac)
			ft_ls_read_info(ls, argv[i++]);
		ft_ls_sort_lists(ls, ls->files);
		validate_dir(ls, ls->files->head);
	}
	else
		ft_ls_read_dir_info(ls, ".");
	ft_ls_printing(ls);
	return (0);
}
