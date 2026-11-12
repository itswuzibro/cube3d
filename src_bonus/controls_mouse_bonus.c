/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_mouse_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:22:41 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 18:46:02 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	mouse_moves(int x, int y, t_data *d)
{
	static int	old_x = -1;

	(void)y;
	if (d->game_state == GAME)
	{
		if (old_x == -1)
			old_x = x;
		if (x < WIDTH && x > old_x)
			d->p.angle += 0.03;
		else if (x > 0 && x < old_x)
			d->p.angle -= 0.03;
		old_x = x;
		if (old_x < MIWIDTH - 100 || old_x > MIWIDTH + 100)
			mlx_mouse_move(d->mlx, d->win, MIWIDTH, MIHEIGHT);
	}
	return (0);
}

int	mouse_buttons(int key, int x, int y, t_data *d)
{
	(void)x;
	(void)y;
	if (key == 1)
		d->p.state = ATTACK;
	return (0);
}

int	mouse_quit(t_data *d)
{
	exit_and_free(d, "Closing game..\n");
	return (0);
}
