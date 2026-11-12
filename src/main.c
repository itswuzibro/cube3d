/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:28:06 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 20:19:50 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	init_structures(t_data *d)
{
	init_data(d);
	init_config(&d->c);
	init_img(&d->i);
	init_keys(&d->k);
	imgs_nullifier(d->wall, 4);
}

void	format_map(t_data *d)
{
	char	**new;
	int		i;
	int		j;

	i = -1;
	new = malloc(sizeof(char *) * (d->c.rows + 1));
	if (!new)
		exit_and_free(d, ALLOC_ERROR);
	while (++i < d->c.rows)
	{
		new[i] = malloc(sizeof(char) * (d->c.cols + 1));
		if (!new[i])
			exit_and_free(d, ALLOC_ERROR);
		ft_memset(new[i], '1', d->c.cols);
		j = -1;
		while (d->c.map[i][++j])
		{
			if (d->c.map[i][j] != ' ')
				new[i][j] = d->c.map[i][j];
		}
		new[i][d->c.cols] = '\0';
	}
	new[i] = NULL;
	ft_free_tab(d->c.map);
	d->c.map = new;
}

void	parsing(t_data *d, char *path)
{
	validate_map_format(d, path);
	stock_sd(d, path);
	get_textures_and_colors(d);
	get_map(d);
	create_flood_map(d);
	fill_flood_map(d);
	flood(d, 0, 0);
	d->c.f_color = extract_rbg_value(d, d->c.f);
	d->c.c_color = extract_rbg_value(d, d->c.c);
	format_map(d);
	verif(d);
	authorized_char(d);
}

static int	event_tick(t_data *d)
{
	d->delta_time = 1.0f * (gettime() - d->last_frame) / 1000;
	d->last_frame = gettime();
	create_frame_image(d, &d->i);
	raycasting(d, &d->p, &d->r);
	update_player(d, d->delta_time);
	mlx_put_image_to_window(d->mlx, d->win, d->i.ptr, 0, 0);
	mlx_destroy_image(d->mlx, d->i.ptr);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	d;

	if (ac == 2)
	{
		srand(time(NULL));
		init_structures(&d);
		parsing(&d, av[1]);
		determine_player_position(&d);
		d.mlx = mlx_init();
		d.win = mlx_new_window(d.mlx, WIDTH, HEIGHT, "cub3d");
		load_game_images(&d);
		mlx_hook(d.win, 2, 1L << 0, control_pressed, &d);
		mlx_hook(d.win, 3, 1L << 1, control_released, &d);
		mlx_hook(d.win, 17, 1L << 1, mouse_quit, &d);
		mlx_loop_hook(d.mlx, event_tick, &d);
		mlx_loop(d.mlx);
		return (0);
	}
}
