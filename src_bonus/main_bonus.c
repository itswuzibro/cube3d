/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:28:06 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 17:48:29 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	hit_reaction(t_data *d)
{
	int		i;
	time_t	now;

	i = 0;
	now = gettime();
	while (i < MAX_BLOOD)
	{
		if (d->p.blood[i].active)
		{
			copypaste_img(d->p.blood[i].img, &d->i,
				d->p.blood[i].pos.x, d->p.blood[i].pos.y);
			if (now - d->p.blood[i].timer > 20)
			{
				d->p.blood[i].timer = now;
				d->p.blood[i].pos.y += d->p.blood[i].vel_y;
				d->p.blood[i].vel_y += 0.2f;
			}
			if (d->p.blood[i].pos.y > HEIGHT)
				d->p.blood[i].active = false;
		}
		i++;
	}
}

static int	event_tick(t_data *d)
{
	time_t	now;

	now = gettime();
	d->delta_time = 1.0f * (now - d->last_frame) / 1000;
	if (d->screen_shake > 0)
		d->screen_shake -= 20.0f * d->delta_time;
	else
		d->screen_shake = 0;
	d->time += d->delta_time;
	d->last_frame = now;
	create_frame_image(d, &d->i);
	if (d->game_state == GAME)
		tick_game(d);
	else if (d->game_state == MENU)
		tick_menu(d);
	else if (d->game_state == PAUSE)
		tick_pause(d);
	else if (d->game_state == END)
		tick_ending(d);
	mlx_put_image_to_window(d->mlx, d->win,
		d->i.ptr, sin(d->time * 20) * d->screen_shake, 0);
	mlx_destroy_image(d->mlx, d->i.ptr);
	d->i.ptr = NULL;
	return (0);
}

int	main(int ac, char **av)
{
	t_data	d;

	if (ac == 2)
	{
		srand(time(NULL));
		d = (t_data){0};
		init_structures(&d);
		file_extract(&d, av[1]);
		file_parse(&d);
		file_use(&d);
		d.mlx = mlx_init();
		if (!d.mlx)
			exit_and_free(&d, "init mlx");
		init_images(&d);
		init_gameplay(&d);
		d.win = mlx_new_window(d.mlx, WIDTH, HEIGHT, "cub3d");
		mlx_hook(d.win, 2, 1L << 0, control_pressed, &d);
		mlx_hook(d.win, 3, 1L << 1, control_released, &d);
		mlx_hook(d.win, 6, 1L << 6, mouse_moves, &d);
		mlx_hook(d.win, 4, 1L << 2, mouse_buttons, &d);
		mlx_hook(d.win, 17, 1L << 1, mouse_quit, &d);
		mlx_loop_hook(d.mlx, event_tick, &d);
		mlx_loop(d.mlx);
		return (0);
	}
}
