/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:25:02 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 20:23:15 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_BONUS_H
# define CUBE_BONUS_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <math.h>
# include <sys/time.h>
# include <time.h>
# include <stdbool.h>

// COLORS
# define BLACK			0x000000
# define RED			0xFF0000
# define GREEN			0x00FF00
# define BLUE			0x0000FF
# define DARK_GREEN		0x296321
# define BROWN			0x181008
# define BLOOD			0x731717
# define GREY			0x646464

# define CASE_WALL		'1'
# define CASE_ROOF		'2'
# define CASE_WINE		'3'
# define CASE_RIVER		'4'
# define CASE_CDOOR		'A'
# define CASE_ODOOR		'B'
# define CASE_FLOOR		'0'
# define CHARSET		"NSEWAB01234"

// CONTROLS
# define LEFT_ARROW		65361
# define RIGHT_ARROW	65363
# define UP_ARROW		65362
# define DOWN_ARROW		65364
# define ENTER			65293
# define SPACE_BAR		32
# define MAJ			65505
# define ECHAP			65307
# define LEFT_CLICK		1

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
# define WIDTH 				1200
# define MIWIDTH			600
# define HEIGHT 			800
# define MIHEIGHT			400
# define RAIN_C				1500
# define PI					3.14159265
# define MAX_P				50
# define MAX_E				50
# define MAX_C				50
# define MAX_BLOOD			20
# define PRO_SCALE_X		0.2f
# define PRO_SCALE_Y		0.2f
# define PRO_ADD_Y			60

# define WEREDRAGON_WMS		1.2f
# define WEREDRAGON_RMS		2.8f
# define WIZARD_WMS			0.9f
# define WIZARD_RMS			1.3f

# define P_BASE_WMS					1.5f
# define P_BASE_RMS					3.0f
# define P_BASE_PMS					4.0f
# define P_BASE_LIFE				1000
# define P_BASE_STAMINA				10.0f
# define P_BASE_POWER_DURATION		8000
# define P_BASE_ATK_INTERVAL		160
# define P_BASE_DAMAGE				50

# define P_LEVEL_MS					0.3f
# define P_LEVEL_LIFE				350
# define P_LEVEL_STAMINA			2.0f
# define P_LEVEL_POWER_DURATION		2000
# define P_LEVEL_ATK_INTERVAL		12
# define P_LEVEL_DAMAGE				15

typedef enum game_state
{
	MENU,
	GAME,
	PAUSE,
	END,
}				t_game_state;

typedef enum character_state
{
	PASSIVE,
	INTERACT,
	ROAM,
	ATTACK,
	DEAD,
	PAIN,
	NUKE,
}				t_state;

typedef enum enemy_type
{
	WIZARD,
	WEREDRAGON
}				t_type;

typedef enum walls
{
	NO,
	SO,
	EA,
	WE,
}				t_walls;

typedef struct s_fvector
{
	float	x;
	float	y;
}				t_fvector;

typedef struct s_ivector
{
	int	x;
	int	y;
}				t_ivector;

typedef struct s_transfom
{
	t_fvector	scale;
	float		add_y;
}				t_transform;

typedef struct s_rain
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	speed;
	int		len;
}				t_rain;

typedef struct s_keyboard
{
	bool	w;
	bool	z;
	bool	a;
	bool	q;
	bool	s;
	bool	d;
	bool	e;
	bool	m;
	bool	space;
	bool	enter;
	bool	maj;
	bool	up_arrow;
	bool	down_arrow;
	bool	left_arrow;
	bool	right_arrow;
}				t_keyboard;

typedef struct s_img
{
	void			*ptr;
	unsigned int	*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}				t_img;

typedef struct s_raycast
{
	double			camera_x;
	t_fvector		ray_dir;
	t_fvector		side_dist;
	t_fvector		delta_dist;
	double			perp_wall_dist;
	t_walls			w;
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
	int				door;
	double			tex_step;
	t_ivector		tex;
	double			tex_pos;
	t_img			*selected_img;
	char			letter;
}				t_raycast;

typedef struct s_floorcast
{
	t_fvector	ray_dir_l;
	t_fvector	ray_dir_r;
	t_fvector	floor_step;
	t_fvector	step;
	t_fvector	floor;
	t_ivector	cell;
	t_ivector	uv;
	float		pos_z;
	int			p;
	float		row_dist;
	t_img		*floor_img;
	t_img		*roof_img;
	char		cell_case;
}				t_floorcast;

typedef struct s_scast
{
	double			sprite_rel_x;
	double			sprite_rel_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				screen_x;
	int				vmove_screen;
	int				sprite_h;
	int				sprite_w;
	int				draw_start_x;
	int				draw_start_y;
	int				draw_end_x;
	int				draw_end_y;
	int				stripe_offset;
	int				stripe;
	int				tex_x;
	int				tex_y;
	int				d_y;
}				t_scast;

typedef struct s_flip
{
	t_img	*frame;
	int		index;
	time_t	last_update;
	bool	stopped;
	bool	completed;
	bool	event;
	bool	event_triggered;
	t_img	*imgs;
	int		loops;
	int		frame_per_dir;
	int		nb_direction;
	int		interval;
	int		event_frame;
	bool	is_durty;
}				t_flip;	

typedef struct s_enemy
{
	t_fvector	pos;
	t_fvector	dir;
	float		ms;
	float		attack_range;
	float		angle;
	int			life;
	t_fvector	point_of_interest;
	int			damages;
	time_t		atk_timer;
	int			atk_interval;
	time_t		wait_timer;
	int			wait_interval;
	t_flip		*current_anim;
	t_flip		idle;
	t_flip		pain;
	t_flip		walk;
	t_flip		run;
	t_flip		attack;
	t_flip		death;
	t_state		state;
	t_type		type;
	t_transform	transform;
	bool		active;
	int			xp_gain;
}				t_enemy;

typedef struct s_projectile
{
	t_fvector			pos;
	t_fvector			dir;
	float				ms;
	float				angle;
	t_flip				*current_anim;
	t_flip				flip_launched;
	t_flip				flip_explode;
	bool				active;
	bool				collided;
	int					damages;
	bool				is_friendly;
	t_transform			transform;
}				t_projectile;

typedef struct s_blood_splat
{
	t_img		*img;
	t_ivector	pos;
	bool		active;
	time_t		timer;
	time_t		interval;
	float		vel_y;
}				t_blood_splat;

typedef struct s_player
{
	t_fvector			pos;
	t_fvector			dir;
	t_fvector			plane;
	t_flip				*current_anim;
	t_flip				attack;
	t_flip				interact;
	t_flip				nuke;
	t_flip				idle;
	float				angle;
	float				rotspeed;
	int					kill_count;
	bool				powered;
	bool				tired;
	bool				dead;
	t_ivector			hands_offset;
	t_state				state;
	t_blood_splat		blood[MAX_BLOOD];
	char				actual_case;
	time_t				cooldown;
	int					level;
	int					xp;
	int					nl_xp;
	float				stamina;
	float				stamina_max;
	int					damage;
	int					life;
	int					life_max;
	time_t				powerdown;
	float				movespeed;
	float				ms_sprint;
	float				ms_walk;
	float				ms_powered;
	time_t				power_duration;
}				t_player;

typedef struct s_collectible
{
	t_fvector			pos;
	t_fvector			dir;
	t_flip				flip;
	float				angle;
	int					xp_gain;
	int					life_gain;
	int					stamina_gain;
	t_transform			transform;
	bool				active;
	int					vel_y;
}				t_collectible;

typedef struct s_portal
{
	t_fvector			pos;
	t_fvector			dir;
	t_flip				*current_anim;
	t_flip				far;
	t_flip				ascending;
	t_flip				descending;
	t_flip				close;
	float				angle;
	t_transform			transform;
}				t_portal;

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
	char			*river_path;
	char			*roof_path;
	unsigned int	c_color;
}				t_config;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	time_t				last_frame;
	float				delta_time;
	bool				weather;
	bool				light;
	bool				menu_light;
	time_t				last_lightning;
	time_t				n_lightning;
	time_t				l_duration;
	int					minimap_size;
	int					minimap_press;
	int					minimap_pix;
	bool				game_launch;
	float				*z_buffer;
	float				time;
	int					transparent;
	float				screen_shake;

	t_config			c;
	t_player			p;
	t_img				i;
	t_raycast			r;
	t_rain				rain[RAIN_C];
	t_keyboard			k;
	t_game_state		game_state;
	t_projectile		projectiles[MAX_P];
	t_enemy				enemies[MAX_E];
	t_img				intro;
	t_img				title;
	t_img				launch;
	t_img				paused;
	t_img				go_on;
	t_img				quit;
	t_img				skull[18];
	t_img				wall[4];
	t_img				floor;
	t_img				roof;
	t_img				door[2];
	t_img				wine;
	t_img				river;
	t_img				player;
	t_img				attack[9];
	t_img				player_nuke[6];
	t_img				interact[4];
	t_img				border[2];
	t_img				status[2];
	t_img				health[2];
	t_img				health_empty;
	t_img				projectile_player[4];
	t_img				projectile_wizard[4];
	t_img				weredragon_walk[48];
	t_img				weredragon_idle[16];
	t_img				weredragon_attack[2];
	t_img				weredragon_death[9];
	t_img				weredragon_pain[8];
	t_img				wizard_walk[32];
	t_img				wizard_idle[16];
	t_img				wizard_pain[8];
	t_img				wizard_atk[3];
	t_img				wizard_death[19];
	t_img				blood_splat[6];
	t_img				portal_far[8];
	t_img				portal_ascending[3];
	t_img				portal_descending[3];
	t_img				portal_close[8];
	t_img				numbers[10];
	t_portal			portal;
	t_img				crosshair;
	t_img				ending;
	time_t				ending_start;
	t_img				right;
	t_img				big_right;
	bool				screen_flood;
	t_ivector			debug;
	t_collectible		col[MAX_C];
}				t_data;

// DATA INITIALIZATION 
void			init_images(t_data *d);
void			init_structures(t_data *d);
void			init_gameplay(t_data *d);
void			init_characters(t_data *d);
void			init_blood(t_data *d);

// IMAGES
void			create_frame_image(t_data *d, t_img *img);
void			new_image(t_data *d, t_img *img, char *path);
int				new_image_ret(t_data *d, t_img *img, char *path);
void			copypaste_img(t_img *src, t_img *dest,
					int start_x, int start_y);
void			copypaste_img_limit(t_img *src, t_img *dest,
					t_ivector start, t_ivector limit);

// SCENE DESCRIPTOR
void			get_textures_and_colors(t_data *d);
unsigned int	extract_rbg_value(t_data *d, char *value);
void			file_use(t_data *d);
void			file_parse(t_data *d);
void			file_extract(t_data *d, char *path);
void			authorized_char(t_data *d);

// MLX BOOSTED
void			mlx_set_pixel(t_img *img, int x, int y, int color);
int				mlx_get_pixel(t_img *img, int x, int y);

// CLEANING
int				mouse_quit(t_data *d);
void			exit_and_free(t_data *d, char *errormsg);
char			*ft_strtrim_secure(t_data *d, char *s1,
					char const *set, int opt);

// TOOLS
unsigned int	create_trgb(int t, int r, int g, int b);
time_t			gettime(void);
int				animation(int nb_img, int fps);
void			imgs_destroyer(t_data *d, t_img *img, int nb_img);
bool			is_floor(char **map, int x, int y);
bool			is_wall(char **map, int x, int y);
bool			is_blocking_ray(char **map, int x, int y);
bool			is_out_of_map(int map_cols, int map_rows, int x, int y);
float			find_angle_to_location(t_fvector start, t_fvector target);
bool			is_walkable(t_data *d, float x, float y, float hitbox_size);
t_fvector		farthest_location(t_data *d);

// TICKS
void			tick_menu(t_data *d);
void			tick_game(t_data *d);
void			tick_pause(t_data *d);
void			tick_ending(t_data *d);

// CASTINGS
void			raycasting(t_data *d, t_player *p, t_raycast *r);
void			init_ray(t_player *p, t_raycast *r);
void			perform_dda(t_data *d, t_raycast *r);
void			select_img_by_letter(t_data *d, t_raycast *r);
void			calculate_wall_size(t_raycast *r);
void			calculate_texture_coor(t_raycast *r, t_player *p);
void			draw(t_data *d, t_raycast *r, int x);
unsigned int	calculate_coor_get_txtr_color(t_raycast *r, unsigned int color);
void			init_floorcasting(t_data *d, t_floorcast *fc);
void			floorcasting(t_data *d);
bool			init_scasting(t_data *d, t_scast *s,
					t_fvector *pos, t_transform *t);

// GAMEPLAY
void			rotate_player(t_data *d, t_player *player, float delta_time);
int				control_pressed(int key, t_data *d);
int				control_released(int key, t_data *d);
int				mouse_moves(int x, int y, t_data *d);
int				mouse_buttons(int key, int x, int y, t_data *d);
void			update_player(t_data *d, t_player *player, float delta_time);
void			update_projectiles(t_data *d, float delta_time);
void			update_enemies(t_data *d, float delta_time);
void			update_stamina(t_data *d, t_player *player, float delta_time);
void			update_flipbook(t_flip *flip);
void			update_collectibles(t_data *d, float deltatime);
void			update_portal(t_data *d);
void			hit_reaction(t_data *d);

// COLLISIONS
void			check_player_collision(t_data *d, t_projectile *projectile);
void			check_projectiles_collisions(t_data *d,
					t_projectile *projectile);
void			check_enemies_collision(t_data *d, t_projectile *projectile);

// FLIPBOOKS
void			set_flip_core(t_flip *flip, t_img *imgs,
					int frame_per_dir, int nb_direction);
void			set_flip_time(t_flip *flip, int loops,
					int interval, int event_frame);
void			reset_flip(t_flip *flip);

// HUD
void			hud(t_data *d);
void			change_minimap_size(t_data *d);
void			minimap(t_data *d);

// ENEMIES EVENTS
void			apply_damage_on_enemy(t_data *d, t_enemy *enemy, int damage);
t_fvector		random_valid_location(t_data *d);
bool			can_see_player(t_data *d, t_fvector start,
					float angle, int view_max);
void			enemy_change_state(t_enemy *enemy, t_state state);
void			enemy_roaming(t_data *d, t_enemy *enemy, float delta_time);
void			enemy_attack(t_data *d, t_enemy *enemy, float delta_time);
void			enemy_passive(t_data *d, t_enemy *enemy);
void			move_enemy(t_data *d, t_enemy *enemy, float delta_time);
void			wizard_attack(t_data *d, t_enemy *wizard, float delta_time);
void			weredragon_attack(t_data *d,
					t_enemy *weredragon, float delta_time);

// PLAYER EVENTS
void			player_interact(t_data *d, t_player *player);
void			player_xp(t_player *player, int xp);
void			apply_damage_on_player(t_data *d, t_player *player, int damage);
void			player_power(t_player *player);
void			player_wipe(t_data *d, t_player *player);
void			player_state_attack(t_data *d, t_player *player);
void			draw_player(t_data *d, t_player *p);

// PROJECTILES
void			launch_projectile(t_data *d, t_fvector pos,
					float angle, bool is_friendly);
void			spritecasting(t_data *d, t_img *img,
					t_fvector pos, t_transform transform);
int				rotate_sprite(t_data *d, t_fvector pos,
					float angle, int num_img);
void			update_sprite_anim(t_data *d, t_flip *flip,
					t_fvector pos, float angle);
float			distance(t_fvector pos_a, t_fvector pos_b);
void			set_projectile_collided(t_projectile *projectile);

// WEATHER
void			rain(t_data *d, t_rain *r, float delta_time);
void			launch_rain(t_data *d);
void			lightning(t_data *d);

void			verif(t_data *d);
t_ivector		make_ivector(int x, int y);
void			draw_numbers(t_data *d, int number, t_ivector start);
void			draw_square(t_data *d, t_ivector pos,
					int size, unsigned int color);

#endif