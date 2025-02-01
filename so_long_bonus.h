/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:49:06 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/28 18:30:23 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "MLX42.h"
# include "libft.h"

# define CELL_WIDTH 16
# define CELL_HEIGHT 30

typedef struct s_params
{
	mlx_t		*mlx;
	char		**map;
	int			move_count;
	int			character_frame;
	char		*character_direction;
	int			opponent_frame;
	char		*opponent_direction;
	int			frame;
	int			frame_counter;
}	t_params;

typedef struct s_map_state
{
	char	**map;
	int		rows;
	int		cols;
	int		collectibles;
	int		exit_found;
}	t_map_state;

void	print_move_count(t_params *params, int on_screen);

void	initialize_map(char *filename, char ***map);
char	**parse_map(const char *filename);
char	**duplicate_map(char **map, int rows, int cols);
void	free_map(char **map, int rows);

int		map_height(char **map);
int		count_lines(const char *filename);
int		count_collectibles(char **map);

int		is_valid_characters_and_shape(char **map);
int		is_closed(char **map);
int		has_required_components(char **map);
int		has_valid_path(char **map);

void	explore(t_map_state *state, int x, int y);

int		find_char_y(char **map, char c);
int		find_char_x(char **map, char c);

void	update_character_position(t_params *params, mlx_key_data_t keydata);
void	update_sprites(t_params *params);
void	update_opponent_position(t_params *params);
void	update_opponent_sprites(t_params *params);

char	*get_sprite_filename(const char *prefix,
			const char *direction, int frame);

void	draw_walls_and_floors(mlx_t *mlx, char **map);
void	draw_file_at(mlx_t *mlx, int cell_x, int cell_y, char *filename);

void	animate_door(t_params *params);
void	add_opponent_to_map(char **map);

#endif