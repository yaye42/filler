/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 11:38:46 by yaye              #+#    #+#             */
/*   Updated: 2019/10/21 11:38:47 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

t_list	*get_fd(t_list *list, int fd)
{
	t_list	*ret;

	if (fd == 0 && !list->content)
	{
		if (!(list->content = malloc(sizeof(void))))
			return (NULL);
		list->content = ft_memcpy(list->content, "\0", 1);
	}
	ret = list;
	while (ret->next && ret->content_size != (size_t)fd)
		ret = ret->next;
	if (ret->content_size != (size_t)fd)
	{
		ret->next = ft_lstnew("\0", (size_t)fd);
		ret = ret->next;
	}
	return (ret);
}

void	clr_fd(t_list *list, int fd)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (fd == 0)
	{
		ft_memdel((void **)&list->content);
		return ;
	}
	tmp = list;
	while (tmp->next && tmp->content_size != (size_t)fd)
		tmp = tmp->next;
	if (tmp->content_size != (size_t)fd)
		return ;
	tmp2 = list;
	while (tmp2->next != tmp)
		tmp2 = tmp2->next;
	tmp2->next = tmp->next;
	ft_memdel((void **)&tmp->content);
	ft_memdel((void **)&tmp);
}

char	*gl(t_list *list, int fd, char **old)
{
	char	*line;
	char	*new;
	int		i;

	i = 0;
	while ((*old)[i] && (*old)[i] != '\n')
		i++;
	if (!(line = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = -1;
	while ((*old)[++i] && (*old)[i] != '\n')
		line[i] = (*old)[i];
	line[i] = 0;
	if ((*old)[i] && (*old)[i + 1])
	{
		if (!(new = ft_strsub((*old), i + 1, ft_strlen((*old)) - i - 1)))
			return (NULL);
		ft_memdel((void **)old);
		(*old) = new;
	}
	else
		clr_fd(list, fd);
	return (line);
}

int		get_next_line(const int fd, char **line)
{
	static t_list		list;
	t_list				*current;
	char				*buf;
	char				*new;
	int					rd;

	if (!(buf = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)) \
		|| fd < 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	current = get_fd(&list, fd);
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[rd] = 0;
		if (!(new = ft_strjoin(current->content, buf)))
			return (-1);
		ft_memdel((void **)&current->content);
		current->content = new;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (!ft_strlen((current->content)))
		return (0);
	(*line) = gl(&list, fd, (char **)&current->content);
	ft_memdel((void **)&buf);
	return (1);
}
