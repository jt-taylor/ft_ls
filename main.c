/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:36:12 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/03 14:48:59 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Standard error msg
*/

static inline void	ft_ls_standard_error(const char flag)
{
	ft_dprintf(2, "ls: illegal option -- %c\nusage ls [-larRt] [file ...]\n", flag);
	exit(1);
}


/*
** Check flags
** this loops through each charector in each argument such that -lar has the
** same functionality as -l -a -r
*/

static inline void	ft_ls_check_flags(t_ft_ls *ls, char **argv, int *i)
{
	while (argv[++(*i)] && argv[*i][0] == '-' && argv[*i][1] && ++argv[*i])
	{
		while (*argv[*i] && *argv[*i] != '\0')
		{
			if (*argv[*i] == 'l')
				ls->flag |= FLAG_L;
			else if (*argv[*i] == 'a')
				ls->flag |= FLAG_A;
			else if (*argv[*i] == 'r')
				ls->flag |= FLAG_R;
			else if (*argv[*i] == 'R')
				ls->flag |= FLAG_RR;
			else if (*argv[*i] == 't')
				ls->flag |= FLAG_T;
			else
				ft_ls_standard_error(*argv[*i]);
			++argv[*i];
		}
	}
}


/*
** main
*/

int		main(int ac, char **argv)
{
	t_ft_ls		*ls;
	int			i;

	i = 0;
	if (!(ls = (t_ft_ls *)malloc(sizeof(t_ft_ls))))
		return (1);
	ft_bzero(ls, sizeof(t_ft_ls));
	if (!(ls->files = (t_ft_ls_dir_info *)malloc(sizeof(t_ft_ls_dir_info))))
		return (1);
	ft_bzero(ls->files, sizeof(t->ft_ls_dir_info));
	if (ac > 1 && argv[1][0] == '-' && argv[1][1])
		ft_ls_check_flags(ls, argv, &i);
	if ((ac > 1 && i < ac && !ls->flag && ++i) || (argc > i && ls->flag))
	{
		while (i < ac)
			ft_ls_read_info(ls, argv[i++]);
		sort lists(ls, ls->files);
		check_dir(ls, ls->files);
	}
	else if (ls->flag & FLAG_D)
		ft_ls_read_info(ls, ".");
	else
		//read_dir_info;
	//output;
	return (0) // Success
}
