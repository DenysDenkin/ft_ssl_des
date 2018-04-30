/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 18:34:11 by ddenkin           #+#    #+#             */
/*   Updated: 2017/11/28 13:59:49 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# define BUFF_SIZE 1

int					get_next_line(const int fd, char **line);

typedef struct		s_buf
{
	int				fd;
	char			*buf;
	struct s_buf	*next;
}					t_buf;
#endif
