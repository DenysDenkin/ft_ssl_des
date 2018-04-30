/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 16:02:06 by ddenkin           #+#    #+#             */
/*   Updated: 2018/01/31 21:12:30 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static int		freebuf(const int fd, t_buf **lst, char **tmp, char **buf)
{
	t_buf *cur;
	t_buf *prev;

	cur = *lst;
	prev = cur;
	if (tmp)
		free(*tmp);
	if (buf)
		free(*buf);
	if (fd < 0)
		return (0);
	while (cur && cur->fd != fd)
	{
		prev = cur;
		cur = cur->next;
	}
	if (!cur)
		return (0);
	prev->next = cur->next;
	free(cur->buf);
	free(cur);
	if (*lst == cur)
		*lst = NULL;
	return (0);
}

static int		writebuf(char *str, const int fd, t_buf **lst)
{
	t_buf	*tmp;
	t_buf	*prev;

	prev = *lst;
	tmp = *lst;
	while (tmp != NULL && tmp->fd != fd)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		if ((tmp = (t_buf *)malloc(sizeof(t_buf))) == NULL)
			return (-1);
		if (prev != NULL)
			prev->next = tmp;
		tmp->fd = fd;
		tmp->next = NULL;
	}
	else
		ft_strdel(&tmp->buf);
	tmp->buf = ft_strdup(str);
	if (*lst == NULL)
		*lst = tmp;
	return (tmp->buf) ? (1) : (-1 + freebuf(fd, lst, NULL, NULL));
}

static int		find_endl(char **tmp, const int fd, char **line, t_buf **lst)
{
	char	*tmp2;

	if ((tmp2 = ft_strchr(*tmp, '\n')) != NULL)
	{
		tmp2[0] = '\0';
		*line = *tmp;
		if (writebuf(tmp2 + 1, fd, lst) < 0)
			return (-1 + freebuf(-1, lst, tmp, NULL));
		if (!*line)
			return (-1);
		return (1);
	}
	return (0);
}

static int		myread(const int fd, char **line, char **tmp, t_buf **lst)
{
	char	*buf;
	int		ret;
	int		fail;
	char	*tmp2;

	if ((buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))) == NULL)
		return (-1);
	buf[BUFF_SIZE] = '\0';
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp2 = *tmp;
		*tmp = ft_strjoin(*tmp, buf);
		free(tmp2);
		if ((fail = find_endl(tmp, fd, line, lst)) != 0)
		{
			if (!*tmp)
				fail = -1;
			return (fail + freebuf(-1, lst, &buf, NULL));
		}
	}
	return (ret + freebuf(-1, lst, &buf, NULL));
}

int				get_next_line(const int fd, char **line)
{
	static t_buf	*lst;
	t_buf			*tmplst;
	char			*tmp;
	int				ret;

	if (BUFF_SIZE < 1 || fd < 0 || !line)
		return (-1);
	tmplst = lst;
	while (tmplst && tmplst->fd != fd)
		tmplst = tmplst->next;
	tmp = (tmplst) ? ft_strdup(tmplst->buf) : ft_strdup("");
	if (!tmp)
		return (-1);
	if (find_endl(&tmp, fd, line, &lst) == 1)
		return (1);
	ret = myread(fd, line, &tmp, &lst);
	if (ret != 0)
		return (ret);
	if (ft_strcmp(tmp, "") != 0)
	{
		*line = tmp;
		freebuf(fd, &lst, NULL, NULL);
		return (*line == NULL) ? (-1) : (1);
	}
	return (ret + freebuf(-1, &lst, &tmp, NULL));
}
