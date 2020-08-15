/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 10:35:55 by yaye              #+#    #+#             */
/*   Updated: 2019/11/28 10:35:56 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

/*
** CHECK IF POSITION i IS A SOLUTION
*/

int		check(t_filler *env, int i)
{
	int		condition;
	int		limit;
	int		j;

	condition = 0;
	limit = env->brd_y - (i % env->brd_y);
	j = 0;
	while (j < env->pce_x * env->pce_y)
	{
		if (env->piece[j] == STAR)
		{
			if ((j % env->pce_y) + 1 > limit || i >= env->brd_size)
				return (0);
			if (env->board[i] == env->player)
				condition = condition + 1;
			else if (env->board[i] > TUMOR && env->board[i] < 0)
				return (0);
		}
		if (j % env->pce_y == env->pce_y - 1)
			i = i + env->brd_y - env->pce_y;
		i = i + 1;
		j = j + 1;
	}
	return ((condition == 1) ? 1 : 0);
}

/*
** EVALUATE HOW GOOD SOLUTION i IS
*/

int		eval(t_filler *env, int i)
{
	int		score;
	int		j;

	score = 0;
	j = -1;
	while (++j < env->pce_x * env->pce_y)
	{
		if (env->piece[j] == STAR && (env->board[i] > 0 \
			|| env->board[i] == TUMOR))
			score = score + env->board[i];
		if (env->piece[j] == STAR && env->board[i] == TUMOR)
			env->tmr = TUMOR;
		if (j % env->pce_y == env->pce_y - 1)
			i = i + env->brd_y - env->pce_y;
		i = i + 1;
	}
	return (score);
}

/*
** DEFINE EARLY BEHAVIOR OF yaye.filler
*/

int		set_tumors(t_filler *env)
{
	int		i;
	int		a;
	int		b;
	int		cond;

	if (env->tmr == STAR)
	{
		i = -1;
		while (++i < env->brd_size)
		{
			a = (env->board[i] == env->player) ? i : a;
			b = (env->board[i] == env->opponent) ? i : b;
		}
		env->tmr = (a % env->brd_y > b % env->brd_y) ? 0 : env->brd_y - 1;
		env->pos = (a < b) ? 1 : 0;
	}
	cond = 0;
	i = (env->tmr >= 0) ? -1 : env->brd_x;
	while (++i < env->brd_x)
		if (env->board[env->tmr + i * env->brd_y] == 0 && (++cond))
			env->board[env->tmr + i * env->brd_y] = TUMOR;
	return (cond);
}

/*
** AFTER FULLY UPDATING PIECE, SOLVE TO GET A POSITION TO FT_PRINTF
*/

void	strong_solve(t_filler *env)
{
	int		save;
	int		score;
	int		tmp;
	int		i;

	if (set_tumors(env))
		spread_creep(env, TUMOR);
	spread_creep(env, env->opponent);
	score = LIMIT;
	i = -1;
	while (++i < env->brd_size)
	{
		if (check(env, i) && (tmp = eval(env, i)) <= score)
		{
			if ((tmp <= score && !env->pos) || (tmp < score && env->pos))
			{
				save = i;
				score = tmp;
			}
		}
	}
	env->pce_x = 0;
	env->pce_y = 0;
	ft_memdel((void **)&env->piece);
	ft_printf("%d %d\n", save / env->brd_y, save % env->brd_y);
}

/*
** UPDATE BOARD OR PIECE WITH LINE FROM GNL
*/

void	update(t_filler *env, char *buf, char c)
{
	int		i;

	i = 0;
	if (c == 'B')
	{
		while (buf[i] && !ft_isvalid(buf[i], 'B'))
			i = i + 1;
		while (ft_isvalid(buf[i], 'B'))
		{
			if (buf[i] == 'O' || buf[i] == 'o')
				env->board[env->pos++] = OO;
			else if (buf[i] == 'X' || buf[i] == 'x')
				env->board[env->pos++] = XX;
			else
				env->board[env->pos++] = 0;
			i = i + 1;
		}
	}
	if (c == 'P')
	{
		while (ft_isvalid(buf[i], 'P'))
			env->piece[env->pos++] = (buf[i++] == '*') ? STAR : 0;
		if (env->pos == env->pce_x * env->pce_y)
			strong_solve(env);
	}
}
