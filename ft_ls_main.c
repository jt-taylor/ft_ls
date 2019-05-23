/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 12:21:55 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/21 03:45:56 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_ls_error_msg(const char flag)
{
	ft_dprintf(2, "ls: illegal option --%c\nusage:ls [-larRtnGd] [file...]\n",
			flag);
}

/*
** this checks for the flags in this manner
** for each argument that starts with '-'
** read through that argument and add the corresponding bit to the
** 		ls->flag bitfield
*/

static inline void	check_flags(t_ft_ls *ls, char **argv, int *i)
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
				ls->flag |= FLAG_UP_R;
			else if (*argv[*i] == 't')
				ls->flag |= FLAG_T;
			else if (*argv[*i] == 'n')
				ls->flag |= FLAG_N;
			else if (*argv[*i] == 'G')
				ls->flag |= FLAG_G;
			else if (*argv[*i] == 'd')
				ls->flag |= FLAG_D;
			else
				ft_ls_error_msg(*argv[*i]);
			++argv[*i];
		}
	}
}

void				ft_error(char *str, char c)
{
	ft_dprintf(2, "ft_ls: %s:%s", str, (c) ? "Permission Denied\n" :
			"No such file or directory\n");
}


/*
** note for future me 
**
** this should never be used in something that doesn't terminate ,
** 		the memory is free by the os on exit , so if this is
** 		used by something like a daemon the memory is never released and
** 		will just sit there untill the maximum process memory limit is reached
** This is conciouslly leaving the cleanup to the os because
** 		this only has to work on scholl macs , and maybe future me needs a the
** 		double linked list somewhere
** i know i am repeating myself but there are no mallocs outside the structs
** 		in the dblnk list , which are all accesible from the main
*/

/*
** sets up the ls structure with ls->files also allocated for
** checks for the flags (uses bitfields to store flags)
** if arguments were provided with no flags or flags were provided
** 		it will read then sort then check directories according to the d flag
** 	or if there was at least the d flag with no arguments
** 		it will list the current dir without recursion of dir's
** 	otherwise it works on the current dir
**
** 	then it prints the collected data
*/

int				main(int ac, char **argv)
{
	t_ft_ls		*ls;
	int			i;

	i = 0;
	if ((ls = (t_ft_ls *)malloc(sizeof(t_ft_ls))) == NULL)
		return (FT_LS_MALLOC_ERROR);
	ft_bzero(ls, sizeof(t_ft_ls));
	if ((ls->files = (t_ft_ls_dir *)malloc(sizeof(t_ft_ls_dir))) == NULL)
		return (FT_LS_MALLOC_ERROR);
	ft_bzero(ls->files, sizeof(t_ft_ls_dir));
	if (ac > 1 && argv[1][0] == '-' && argv[1][1])
		check_flags(ls, argv, &i);
	if ((ac > 1 && i < ac && !ls->flag && ++i) || (ac > i && ls->flag))
	{
		while (i < ac)
			ft_ls_read_info(ls, argv[i++]);
		ft_ls_sort_list_elem(ls, ls->files);
		ft_ls_check_if_dir(ls, ls->files->head);
	}
	else if (ls->flag & FLAG_D)
		ft_ls_read_info(ls, ".");
	else
		ft_ls_read_dir_info(ls, ".");
	ft_ls_printing(ls);
	return (0);
}
