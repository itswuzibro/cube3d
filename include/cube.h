/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:25:02 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 20:23:06 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <math.h>
# include <sys/time.h>
# include <time.h>
# include <stdbool.h>

// PARSING
# define CHARSET		"NSEW01"

// COLORS
# define BLACK			0x00000000
# define RED			0x00FF0000
# define GREEN			0x0000FF00
# define BLUE			0x000000FF
# define DARK_GREEN		0x296321
# define BROWN			0x181008
# define BLOOD			0x731717

// KEYBOARD CONTROLS
# define MAJ			65505
# define LEFT_ARROW		65361
# define RIGHT_ARROW	65363
# define UP_ARROW		65362
# define DOWN_ARROW		65364
# define ENTER			65293
# define SPACE_BAR		32
# define ECHAP			65307

// MOUSE CONTROLS
# define LEFT_CLICK		1
# define MIDDLE_CLICK	2
# define RIGHT_CLICK	3

//ERROR MESSAGES
# define FORMAT_ERROR	"Error: Map format is invalid.\n"
# define FLOOD_ERROR	"Error: Map has been flooded.\n"
# define MAP_ERROR		"Error: Map has unauthorized char.\n"
# define ALLOC_ERROR	"Error: Allocation failed.\n"
# define FD_ERROR		"Error: Bad file descriptor.\n"
# define IMG_ERROR		"Error: Failed loading image.\n"
# define PATH_ERR		"Error: No path found.\n"
# define SD_ERR			"Error: Scene descriptor rule broken.\n"
# define TXTR_ERR		"Error: Texture missing.\n"
# define PLAYER_ERR		"Error: Need 1 player.\n"
# define RGB_ERR		"Error: Wrong RGB value(s).\n"
# define RGB_VAL		"Error: RGB values need to be > 0 && <= 255.\n"

// GAME VARIABLES
# define WIDTH 			1200
# define MIWIDTH		600
# define HEIGHT 		800
# define MIHEIGHT		400
# define PI				3.14159265

enum e_WALLS
{
	NO,
	SO,
	EA,
	WE,
};

typedef struct s_keyboard
{
	bool	w;
	bool	z;
	bool	a;
	bool	q;
	bool	s;
	bool	d;
	bool	m;
	bool	enter;
	bool	maj;
	bool	up_arrow;
	bool	down_arrow;
	bool	left_arrow;
	bool	right_arrow;

}		t_keyboard;

typedef struct s_dvector
{
	double	x;
	double	y;
}				t_dvector;

typedef struct s_ivector
{
	int	x;
	int	y;
}				t_ivector;

typedef struct s_player
{
	t_dvector	pos;
	t_dvector	dir;
	t_dvector	plane;

	float		angle;
	float		movespeed;
	float		rotspeed;
	int			hands_offset;
}		t_player;

typedef struct s_raycast
{
	double			camera_x;
	t_dvector		ray_dir;
	t_dvector		side_dist;
	t_dvector		delta_dist;
	double			perp_wall_dist;
	enum e_WALLS	w;
	int				map_x;
	int				map_y;
	t_ivector		map_cell;
	t_ivector		step;
	int				side;
	int				lineheight;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	unsigned int	color;
	double			tex_step;
	t_ivector		tex;
	double			tex_pos;
}		t_raycast;

typedef struct s_img
{
	void			*ptr;
	unsigned int	*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}		t_img;

typedef struct s_config
{
	char			**sd;
	char			**map;
	char			**to_flood;
	int				cols;
	int				rows;

	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	char			*f;
	char			*c;
	unsigned int	f_color;
	unsigned int	c_color;
}				t_config;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	int				line_count;
	int				line_lenght;
	time_t			last_frame;
	float			delta_time;
	bool			is_launch;
	int				debug;

	t_config		c;
	t_player		p;
	t_img			i;
	t_raycast		r;
	t_keyboard		k;
	t_img			wall[4];
}		t_data;

// DATA INITIALIZATION 
void			init_data(t_data *d);
void			init_img(t_img *img);
void			init_keys(t_keyboard *k);
void			init_config(t_config *config);

//IMAGES
void			create_frame_image(t_data *d, t_img *img);
void			new_image(t_data *d, t_img *img, char *path);
void			load_game_images(t_data *d);
void			copypaste_img(t_img *src, t_img *dest,
					int start_x, int start_y);

// SCENE DESCRIPTOR
void			stock_sd(t_data *d, char *path);
void			get_textures_and_colors(t_data *d);
unsigned int	extract_rbg_value(t_data *d, char *value);

// PARSING
void			validate_map_format(t_data *d, char *s);
void			create_flood_map(t_data *d);
void			flood(t_data *d, int x, int y);
void			fill_flood_map(t_data *d);
void			get_map(t_data *d);
void			authorized_char(t_data *d);
void			verif(t_data *d);

// RAYCASTING
void			raycasting(t_data *d, t_player *p, t_raycast *r);
void			init_ray(t_player *p, t_raycast *r);

// MLX BOOSTED
void			mlx_set_pixel(t_img *img, int x, int y, int color);
int				mlx_get_pixel(t_img *img, int x, int y);

//TOOLS
unsigned int	create_trgb(int t, int r, int g, int b);
time_t			gettime(void);
void			imgs_nullifier(t_img *img, int nb_img);
void			imgs_destroyer(t_data *d, t_img *img, int nb_img);

// CLEANING
int				mouse_quit(t_data *d);
void			exit_and_free(t_data *d, char *errormsg);
char			*ft_strtrim_secure(t_data *d, char *s1,
					char const *set, int opt);

// GAMEPLAY
void			determine_player_position(t_data *d);
void			rotate_player(t_data *d, float delta_time);
int				control_pressed(int key, t_data *d);
int				control_released(int key, t_data *d);
void			update_player(t_data *d, float delta_time);
#endif