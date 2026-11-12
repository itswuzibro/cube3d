/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:59:51 by injah             #+#    #+#             */
/*   Updated: 2025/09/19 20:22:01 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	xload(t_data *d, t_img *stock_location, char *path, int x)
{
	int		i;
	char	*str;

	i = 0;
	while (i < x)
	{
		str = ft_strjoin(path, ft_itoa(i + 1), 2);
		if (!str)
			exit_and_free(d, ALLOC_ERROR);
		str = ft_strjoin(str, ".xpm", 1);
		if (!str)
			exit_and_free(d, ALLOC_ERROR);
		if (new_image_ret(d, &stock_location[i], str) == -1)
		{
			write(2, str, ft_strlen(str));
			free(str);
			exit_and_free(d, IMG_ERROR);
		}
		free(str);
		i++;
	}
}

static void	load_hud_images(t_data *d)
{
	xload(d, d->skull, "imgs/skull/skull", 18);
	new_image(d, &d->intro, "imgs/hud/intro.xpm");
	new_image(d, &d->title, "imgs/hud/titlev3.xpm");
	new_image(d, &d->launch, "imgs/hud/launch_game.xpm");
	new_image(d, &d->go_on, "imgs/hud/continue.xpm");
	new_image(d, &d->paused, "imgs/hud/paused.xpm");
	new_image(d, &d->quit, "imgs/hud/quit0.xpm");
	new_image(d, &d->status[0], "imgs/hud/status_bar.xpm");
	new_image(d, &d->status[1], "imgs/hud/status_power_bar.xpm");
	new_image(d, &d->health[0], "imgs/hud/health_bar.xpm");
	new_image(d, &d->health[1], "imgs/hud/ghealth_bar.xpm");
	new_image(d, &d->border[0], "imgs/hud/border_sprint_bar.xpm");
	new_image(d, &d->border[1], "imgs/hud/gborder_sprint_bar.xpm");
	new_image(d, &d->crosshair, "imgs/hud/crosshair.xpm");
	new_image(d, &d->ending, "imgs/hud/ending.xpm");
	new_image(d, &d->right, "imgs/hud/right.xpm");
	new_image(d, &d->big_right, "imgs/hud/bigright.xpm");
	xload(d, d->numbers, "imgs/hud/numbers", 10);
	new_image(d, &d->health_empty, "imgs/hud/health_bar_empty.xpm");
}

static void	load_config_images(t_data *d)
{
	new_image(d, &d->wall[NO], d->c.no);
	new_image(d, &d->wall[SO], d->c.so);
	new_image(d, &d->wall[EA], d->c.ea);
	new_image(d, &d->wall[WE], d->c.we);
	new_image(d, &d->floor, d->c.f);
	if (d->c.river_path)
		new_image(d, &d->river, d->c.river_path);
	if (d->c.roof_path)
		new_image(d, &d->roof, d->c.roof_path);
}

static void	load_game_images(t_data *d)
{
	xload(d, d->projectile_player, "imgs/projectile/projectile_blue", 4);
	xload(d, d->projectile_wizard, "imgs/projectile/projectile_purple", 4);
	xload(d, d->wizard_walk, "imgs/wizard/wizard_walk", 32);
	xload(d, d->wizard_death, "imgs/wizard/wizard_death", 19);
	xload(d, d->wizard_atk, "imgs/wizard/wizard_attack", 3);
	xload(d, d->wizard_idle, "imgs/wizard/wizard_idle", 16);
	xload(d, d->wizard_pain, "imgs/wizard/wizard_pain", 8);
	xload(d, d->weredragon_walk, "imgs/weredragon/weredragon_walk", 48);
	xload(d, d->weredragon_attack, "imgs/weredragon/weredragon_attack", 2);
	xload(d, d->weredragon_death, "imgs/weredragon/weredragon_death", 9);
	xload(d, d->weredragon_idle, "imgs/weredragon/weredragon_idle", 16);
	xload(d, d->weredragon_pain, "imgs/weredragon/weredragon_pain", 8);
	xload(d, d->attack, "imgs/player/player_attack", 9);
	xload(d, d->player_nuke, "imgs/player/player_nuke", 6);
	xload(d, d->interact, "imgs/player/player_interact", 4);
	new_image(d, &d->player, "imgs/player/player_idle1.xpm");
	new_image(d, &d->wine, "imgs/wine.xpm");
	xload(d, d->door, "imgs/door", 2);
	xload(d, d->portal_far, "imgs/portal/portal_far", 8);
	xload(d, d->portal_ascending, "imgs/portal/portal_asc", 3);
	xload(d, d->portal_descending, "imgs/portal/portal_desc", 3);
	xload(d, d->portal_close, "imgs/portal/portal_close", 8);
	xload(d, d->blood_splat, "imgs/blood/bloodsplat", 6);
}

void	init_images(t_data *d)
{
	load_hud_images(d);
	load_game_images(d);
	load_config_images(d);
}
