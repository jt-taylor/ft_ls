/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sl_get_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:10:23 by jtaylor           #+#    #+#             */
/*   Updated: 2019/06/25 15:48:33 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** i don't think that i am going to handle xattr  &&  acl
*/

/*
** gets the mode charector
** ie the leading 'd' etc.
*/
static inline void		check_type(const unsigned int *mode, char *str)
{
	if (S_ISDIR(*mode))
		str[0] = 'd';
	else if (S_ISBLK(*mode))
		str[0] = 'b';
	else if (S_ISCHR(*mode))
		str[0] = 'c';
	else if (S_ISLNK(*mode))
		str[0] = 'l';
	else if (S_ISFIFO(*mode))
		str[0] = 'p';
	else if (S_ISSOCK(*mode))
		str[0] = 's';
	else
		str[0] = '-';
}

/*
** fill in leading char
** fill read/write execute permission for user/group/all
** recheck for setuid/setgid bits (runs as user who made file instead of who
** 	invokes it
**	's' if both setgid bit and executable bit are both set
**	'S' if only the setuid/setgid bit is set and not the executable bit
**	't' && 'T' for sticky bit , acts like 's' && 'S' but placed in other
**	even though it is for group , apparently no longer pins the file into
**	memory and only matters when on a directory where it controlls whether
**	people in the group can delete a file in that directory
*/

void		check_mode(unsigned int mode, char *str)
{
	check_type((const unsigned int *)&mode, str);
	str[1] = (char)((mode & S_IRUSR) ? 'r' : '-');
	str[2] = (char)((mode & S_IWUSR) ? 'w' : '-');
	str[3] = (char)((mode & S_IXUSR) ? 'x' : '-');
	str[4] = (char)((mode & S_IRGRP) ? 'r' : '-');
	str[5] = (char)((mode & S_IWGRP) ? 'w' : '-');
	str[6] = (char)((mode & S_IXGRP) ? 'x' : '-');
	str[7] = (char)((mode & S_IROTH) ? 'r' : '-');
	str[8] = (char)((mode & S_IWOTH) ? 'w' : '-');
	str[9] = (char)((mode & S_IXOTH) ? 'x' : '-');
	if (mode & S_ISUID)
		str[3] = (char)((mode & S_IXUSR) ? 's' : 'S');
	if (mode & S_ISGID)
		str[6] = (char)((mode & S_IXGRP) ? 's' : 'S');
	if (mode & S_ISVTX)
		str[9] = (char)((mode & S_IXOTH) ? 't' : 'T');
}
