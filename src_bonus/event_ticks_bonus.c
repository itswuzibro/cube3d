/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_ticks_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:43:43 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 19:25:55 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	tick_menu(t_data *d)
{
	if (d->k.enter == true && d->game_launch == true)
		d->game_state = GAME;
	if (d->k.enter == true && d->game_launch == false)
		exit_and_free(d, "Closing game...\n");
	if (d->k.up_arrow || d->k.w || d->k.a)
		d->game_launch = true;
	if (d->k.down_arrow || d->k.s)
		d->game_launch = false;
	lightning(d);
	launch_rain(d);
	copypaste_img(&d->title, &d->i, MIWIDTH - d->title.width / 2,
		MIHEIGHT - d->title.height - 150);
	if (d->game_launch == true)
		copypaste_img(&d->skull[animation(17, 60)], &d->i,
			WIDTH * 0.25 - d->skull->width * 0.5, MIHEIGHT - d->skull->height);
	else
		copypaste_img(&d->skull[animation(17, 60)], &d->i,
			WIDTH * 0.25 - d->skull->width * 0.5,
			HEIGHT * 0.5 - d->skull->height + 200);
	copypaste_img(&d->launch, &d->i,
		MIWIDTH - d->launch.width / 2, MIHEIGHT - d->launch.height);
	copypaste_img(&d->quit, &d->i,
		MIWIDTH - d->quit.width / 2, MIHEIGHT - d->launch.height + 180);
}

void	tick_game(t_data *d)
{
	raycasting(d, &d->p, &d->r);
	if (d->weather == true)
	{
		if (d->p.actual_case != CASE_ROOF && d->p.actual_case != CASE_ODOOR)
		{
			launch_rain(d);
			lightning(d);
		}
	}
	else
		d->light = true;
	update_projectiles(d, d->delta_time);
	update_enemies(d, d->delta_time);
	(update_stamina(d, &d->p, d->delta_time), update_portal(d));
	spritecasting(d, d->portal.current_anim->frame,
		d->portal.pos, d->portal.transform);
	if (distance (d->p.pos, d->portal.pos) < 0.5f)
	{
		d->ending_start = gettime();
		d->game_state = END;
	}
	update_collectibles(d, d->delta_time);
	update_player(d, &d->p, d->delta_time);
	hit_reaction(d);
	hud(d);
}

void	tick_pause(t_data *d)
{
	raycasting(d, &d->p, &d->r);
	if (d->k.enter == true && d->game_launch == true)
		d->game_state = GAME;
	if (d->k.enter == true && d->game_launch == false)
		exit_and_free(d, "Closing game...\n");
	if (d->k.up_arrow == true)
		d->game_launch = true;
	else if (d->k.down_arrow)
		d->game_launch = false;
	lightning(d);
	launch_rain(d);
	copypaste_img(&d->paused, &d->i,
		MIWIDTH - d->paused.width * 0.5, HEIGHT * 0.20);
	if (d->game_launch == true)
		copypaste_img(&d->skull[animation(17, 60)], &d->i,
			WIDTH * 0.30 - d->skull->width / 2,
			MIHEIGHT - d->skull->height / 2);
	else
		copypaste_img(&d->skull[animation(17, 60)], &d->i,
			WIDTH * 0.30 - d->skull->width / 2,
			MIHEIGHT - d->skull->height / 2 + 200);
	copypaste_img(&d->go_on, &d->i,
		MIWIDTH - d->go_on.width / 2, MIHEIGHT - d->go_on.height / 2);
	copypaste_img(&d->quit, &d->i,
		MIWIDTH - d->quit.width / 2, MIHEIGHT - d->quit.height / 2 + 200);
}

static void	flooding_screen(t_data *d)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			copypaste_img(&d->right, &d->i, x, y);
			x += d->right.width;
		}
		y += d->right.height;
	}
	d->screen_flood = true;
}

void	tick_ending(t_data *d)
{
	time_t	now;

	now = gettime();
	if (now - d->ending_start >= 7500)
		flooding_screen(d);
	else
	{
		copypaste_img(&d->ending, &d->i, WIDTH / 2 - d->ending.width / 2,
			MIHEIGHT - d->ending.height / 2);
		if (now - d->ending_start >= 4000)
			copypaste_img(&d->right, &d->i, 100, 300);
		if (now - d->ending_start >= 5000)
			copypaste_img(&d->right, &d->i, 500, 700);
		if (now - d->ending_start >= 6000)
			copypaste_img(&d->right, &d->i, 900, 400);
		if (now - d->ending_start >= 6500)
			copypaste_img(&d->right, &d->i, 400, 100);
		if (now - d->ending_start >= 7000)
			copypaste_img(&d->right, &d->i, 850, 600);
		if (now - d->ending_start >= 7250)
			copypaste_img(&d->right, &d->i, 900, 200);
	}
	if (d->screen_flood == true && now - d->ending_start >= 11000)
		exit_and_free(d, "Thank you for playing!\n");
}
