NAME = cub3D

NAME_BONUS = cub3D_bonus

SRC =	main.c					\
		mlx.c					\
		init.c					\
		images.c				\
		parsing.c				\
		parsing2.c				\
		cleaning.c				\
		scene_descriptor.c		\
		position_orientation.c	\
		textures_colors.c		\
		raycasting.c			\
		init_raycasting.c		\
		tools.c					\
		controls.c				\
		player.c				\

SRC_BONUS =	cleaning_bonus.c				\
			controls_keyboard_bonus.c		\
			controls_mouse_bonus.c			\
			event_ticks_bonus.c				\
			events_enemies_bonus.c			\
			events_player_bonus.c			\
			events_projectiles_bonus.c		\
			file_extract_bonus.c			\
			file_parse_bonus.c				\
			file_parse_map_bonus.c			\
			file_textures_colors_bonus.c	\
			file_use_bonus.c				\
			init_characters_bonus.c			\
			init_blood_bonus.c				\
			init_flipbooks_bonus.c			\
			init_floorcasting_bonus.c		\
			init_gameplay_bonus.c			\
			init_images_bonus.c				\
			init_raycasting_bonus.c			\
			init_spritecasting_bonus.c		\
			init_structures_bonus.c			\
			main_bonus.c					\
			render_floor_bonus.c			\
			render_HUD_bonus.c				\
			render_minimap_bonus.c			\
			render_raycasting_bonus.c		\
			render_raycasting2_bonus.c		\
			render_sprite_bonus.c			\
			render_sprite2_bonus.c			\
			render_weather_bonus.c			\
			tools_drawing_bonus.c			\
			tools_gameplay_bonus.c			\
			tools_time_bonus.c				\
			tools_image_bonus.c				\
			tools_vector_bonus.c			\
			update_collectibles_bonus.c		\
			update_collisions_bonus.c		\
			update_enemies_attacks_bonus.c	\
			update_enemies_bonus.c			\
			update_enemies_state_bonus.c	\
			update_flipbook_bonus.c			\
			update_player_bonus.c			\
			update_player_state_bonus.c		\
			update_portal_bonus.c			\
			update_projectiles_bonus.c		\
			update_stamina_bonus.c			\

COMPIL = cc

FLAGS = -g3 -Wall -Werror -Wextra

LIBFT = libft/

LINKLIBFT = -Llibft -lft

INCLUDE = include/cube.h

INCLUDE_BONUS = include/cube_bonus.h

OBJ = $(SRC:%.c=$(DIR)/%.o)

OBJ_BONUS = $(SRC_BONUS:%.c=$(DIR)/%.o)

DIR = obj

MLX = ./mlx

LINKMLX = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11

LINKMATHLIB = -lm

$(DIR)/%.o: src/%.c $(INCLUDE)
	mkdir -p $(DIR)
	$(COMPIL) $(FLAGS) -Iinclude -c $< -o $@

all: $(NAME) Makefile

$(NAME) : mlx $(OBJ)
	make -C $(LIBFT)
	make -C $(MLX)
	$(COMPIL) $(FLAGS) $(OBJ) $(LINKLIBFT) $(LINKMLX) $(LINKMATHLIB) -o $(NAME)

bonus: $(NAME_BONUS) Makefile

mlx :
	git clone https://github.com/42Paris/minilibx-linux.git mlx
	make -C mlx

$(NAME_BONUS) : mlx $(OBJ_BONUS)
	make -C $(LIBFT)
	make -C $(MLX)
	$(COMPIL) $(FLAGS) $(OBJ_BONUS) $(LINKLIBFT) $(LINKMLX) $(LINKMATHLIB) -o $(NAME_BONUS)

$(DIR)/%.o: src_bonus/%.c $(INCLUDE_BONUS)
	mkdir -p $(DIR)
	$(COMPIL) $(FLAGS) -Iinclude -c $< -o $@

clean: 
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)
	rm -rf $(MLX)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re