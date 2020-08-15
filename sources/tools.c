/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 10:40:04 by yaye              #+#    #+#             */
/*   Updated: 2019/11/28 10:40:05 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** CHECK IF x IS A CONTENT OF THE BOARD/PIECE (DEPENDING OF c VALUE)
*/

int		ft_isvalid(int x, int c)
{
	if (c == 'B')
	{
		if (x == '.' || x == 'O' || x == 'o' \
			|| x == 'X' || x == 'x')
			return (1);
		return (0);
	}
	else if (c == 'P')
	{
		if (x == '.' || x == '*')
			return (1);
		return (0);
	}
	return (0);
}

/*
** ADJACENT EMPTY BOXES GET VALUE == DISTANCE TO OPPONENT
*/

void	contamine(t_filler *env, int i, int t)
{
	if (i % env->brd_y + 1 < env->brd_y && env->board[i + 1] == 0)
		env->board[i + 1] = t;
	if (i % env->brd_y - 1 >= 0 && env->board[i - 1] == 0)
		env->board[i - 1] = t;
	if (i + env->brd_y < env->brd_size && env->board[i + env->brd_y] == 0)
		env->board[i + env->brd_y] = t;
	if (i - env->brd_y >= 0 && env->board[i - env->brd_y] == 0)
		env->board[i - env->brd_y] = t;
}

/*
** FANCY WAY OF NAMING THE HEATMAP FUNCTION
*/

void	spread_creep(t_filler *env, int t)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = (t == env->opponent) ? -1 : 0;
	while (++i < env->brd_size)
	{
		if (env->board[i] == t && (++j))
			contamine(env, i, (t == TUMOR || t == env->opponent) ? 1 : t + 1);
		if (i == env->brd_size - 1 && j)
		{
			i = -1;
			j = 0;
			t = (t == TUMOR || t == env->opponent) ? 1 : t + 1;
		}
	}
	if (k)
	{
		while (++k < env->brd_size)
			if (!env->board[k])
				env->board[k] = 20;
	}
}
