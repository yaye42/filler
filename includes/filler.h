/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:21:58 by yaye              #+#    #+#             */
/*   Updated: 2019/10/14 18:22:00 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# define OO -1
# define XX -2
# define STAR -3
# define TUMOR -4
# define LIMIT 1440000

/*
** >-------------------------- FILLER ENVIRONMENT ----------------------------<
*/

typedef struct		s_filler
{
	int				player;
	int				opponent;
	int				pos;
	int				tmr;
	int				*board;
	int				brd_x;
	int				brd_y;
	int				brd_size;
	int				*piece;
	int				pce_x;
	int				pce_y;
}					t_filler;

/*
** >------------------------------ FUNCTIONS ---------------------------------<
*/

int		ft_isvalid(int smp, int c);
void	update(t_filler *env, char *buf, char c);
void	spread_creep(t_filler *env, int t);

#endif
