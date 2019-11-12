/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 14:25:41 by bford             #+#    #+#             */
/*   Updated: 2019/11/12 15:19:06 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_clean_all(t_gnl *lst)
{
	t_gnl	*copy;

	while (lst)
	{
		if (lst->content)
			ft_strdel(&(lst->content));
		copy = lst->next;
		free(lst);
		lst = copy;
	}
	return (-1);
}

t_gnl	*ft_lstnew_gnl(int fd)
{
	t_gnl	*new;

	if (!(new = (t_gnl *)malloc(sizeof(t_gnl) * 1)))
		return (NULL);
	new->content = NULL;
	new->nfd = fd;
	new->next = NULL;
	return (new);
}

int		finish(t_gnl **lst, char **line, t_gnl **l_copy)
{
	if ((!(*lst)->content && !(*line = NULL)) || !ft_strlen((*lst)->content))
		return (0);
	if (!(*line = ft_strdup((*lst)->content)))
		return (-1);
	ft_strdel(&((*lst)->content));
	*lst = *l_copy;
	return (1);
}

static int		find_lst(t_gnl **lst, t_gnl **l_copy, int fd)
{
	if (!(*lst))
		if (!(*lst = ft_lstnew_gnl(fd)))
			return (-1);
	*l_copy = *lst;
	while ((*lst)->nfd != fd && (*lst)->next)
		*lst = (*lst)->next;
	if ((*lst)->nfd != fd)
	{
		if (!((*lst)->next = ft_lstnew_gnl(fd)))
			return (-1);
		*lst = (*lst)->next;
	}
	return (1);
}

static int		check(char **con, char **line, t_gnl **l_copy, t_gnl **lst)
{
	char	*p;
	char	*p2;

	if (!(*con) || !(ft_strchr(*con, '\n')))
		return (0);
	p = ft_strchr(*con, '\n');
	p2 = *con;
	*p++ = '\0';
	if (!(*line = ft_strdup(*con)))
		return (-1);
	if (!(*con = ft_strdup(p)))
	{
		ft_strdel(line);
		return (-1);
	}
	free(p2);
	*lst = *l_copy;
	return (1);
}

int		get_next_line(int fd, char **line, int clean)
{
	static t_gnl	*lst;
	char			buff[BUFF_SIZE + 1];
	int				t;
	t_gnl			*l_copy;

	if (clean)
		return (ft_clean_all(lst));
	if (fd < 0 || !line || read(fd, buff, 0) < 0 ||
	find_lst(&lst, &l_copy, fd) == -1)
		return (-1);
	if ((t = check(&(lst->content), line, &l_copy, &lst)))
		return (t);
	while ((t = read(fd, buff, BUFF_SIZE)))
	{
		buff[t] = '\0';
		if (lst->content)
			lst->content = ft_strjoin_free(lst->content, buff);
		else
			lst->content = ft_strdup(buff);
		if ((t = check(&(lst->content), line, &l_copy, &lst)))
			return (t);
	}
	return (finish(&lst, line, &l_copy));
}
