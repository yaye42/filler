/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 10:33:30 by yaye              #+#    #+#             */
/*   Updated: 2019/11/28 10:33:33 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "filler.h"

void	boot(t_filler *env, char *buf)
{
	while ((*buf) && !ft_isdigit(*buf))
		buf++;
	env->player = (*buf == '1') ? OO : XX;
	env->opponent = (*buf == '1') ? XX : OO;
	env->tmr = STAR;
	env->board = 0;
	env->brd_x = 0;
	env->brd_y = 0;
	env->piece = 0;
	env->pce_x = 0;
	env->pce_y = 0;
}

int		*ft_newtab(int x, int y)
{
	int		*new;
	int		i;

	if (!(new = (int *)malloc(sizeof(int) * (x * y))))
		return (0);
	i = 0;
	while (i < (x * y))
		new[i++] = 0;
	return (new);
}

/*
** INDICATE IF buf IS FROM THE BOARD/PIECE
*/

int		disbp(t_filler *env, char *buf, char c)
{
	int		i;
	int		len;

	i = 0;
	while (buf[i] && !ft_isvalid(buf[i], c))
		i = i + 1;
	len = 0;
	while (ft_isvalid(buf[i + len], c))
		len = len + 1;
	if (c == 'B' && i > 0 && len == env->brd_y)
		return (1);
	if (c == 'P' && i == 0 && len == env->pce_y)
		return (1);
	return (0);
}

void	get_size(t_filler *env, char *buf, char c)
{
	int		i;

	i = 0;
	while (buf[i] && !ft_isdigit(buf[i]))
		i++;
	if (c == 'B' && !env->board)
	{
		while (ft_isdigit(buf[i]))
			env->brd_x = env->brd_x * 10 + (buf[i++] - '0');
		while (ft_isdigit(buf[++i]))
			env->brd_y = env->brd_y * 10 + (buf[i] - '0');
		if ((env->brd_size = env->brd_x * env->brd_y) > LIMIT)
			return ;
		env->board = ft_newtab(env->brd_x, env->brd_y);
	}
	if (c == 'P')
	{
		while (ft_isdigit(buf[i]))
			env->pce_x = env->pce_x * 10 + (buf[i++] - '0');
		while (ft_isdigit(buf[++i]))
			env->pce_y = env->pce_y * 10 + (buf[i] - '0');
		env->piece = ft_newtab(env->pce_x, env->pce_y);
	}
	env->pos = 0;
}

int		main(void)
{
	t_filler	env;
	char		*buf;

	while (get_next_line(0, &buf))
	{
		if (ft_strstr(buf, "$"))
			boot(&env, buf);
		else if (ft_strstr(buf, "Plateau"))
			get_size(&env, buf, 'B');
		else if (ft_strstr(buf, "Piece"))
			get_size(&env, buf, 'P');
		else if (disbp(&env, buf, 'B'))
			update(&env, buf, 'B');
		else if (disbp(&env, buf, 'P'))
			update(&env, buf, 'P');
		ft_memdel((void **)&buf);
	}
	ft_memdel((void **)&env.board);
}
