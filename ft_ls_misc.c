/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:56:38 by jtaylor           #+#    #+#             */
/*   Updated: 2019/07/08 13:09:11 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** this checks that the file for a dir has the 'd' mode
** then reads the data for the dir
*/
void		validate_dir(t_ls *ls, t_file_info *file)
{
	while (file)
	{
		(file->mode[0] == 'd') ? ft_ls_read_dir_info(ls, file->name_file) : 0;
		file = file->next;
	}
}

/*
** this is basically strjoin but it is adding the '/' instead of calling strjoin
** an extra time
** somtimes mallocs an extra (char) if the end of the s1 is already '/'
*/

char	*ft_join_dir(const char *s1, const char *s2)
{
	char	*d;
	char	*start;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(d = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2))))
		return (NULL);
	start = d;
	ft_bzero(d, (ft_strlen(s1) + ft_strlen(s2) + 2));
	while (*s1 != '\0')
		*d++ = *s1++;
	if (*(s1 - 1) != '/')
		*d++ = '/';
	while (*s2 != '\0')
		*d++ = *s2++;
	*d = '\0';
	return (start);
}

/*
** this returns the number of charectors needed to a  number in a given base
*/
size_t		ft_nbrlen(intmax_t num, uint8_t base)
{
	size_t	c;
	
	if (num >= 0)
		c = 1;
	else if (num < 0)
		c = 2;
	while (num / base != 0)
	{
		num /= base;
		c++;
	}
	return (c);
}

/*
** do i really need to explain what this does
** also why did i not just make this a macro if it is only one comamnd
** 		the world may never know
*/
void		ft_ls_error(char *str, char witch)
{
	ft_dprintf(2, "ft_ls: %s: %s", str, ((witch) ? ": Permission denied\n" :\
				": No such file or directory\n"));
}
