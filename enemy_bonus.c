/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:49:31 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/01 20:23:35 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	add_opponent_to_map(char **map)
{
	int	y;
	int	x;

	x = find_char_x(map, '0');
	y = find_char_y(map, '0');
	if (x != -1 && y != -1)
		map[y][x] = 'O';
}

void	handle_collision(t_params *params, int *new_x, int *new_y)
{
	int	current_x;
	int	current_y;

	current_x = find_char_x(params->map, 'O');
	current_y = find_char_y(params->map, 'O');
	if (params->map[*new_y][*new_x] == '1'
		|| params->map[*new_y][*new_x] == 'C'
		|| params->map[*new_y][*new_x] == 'E')
	{
		if (ft_strcmp(params->opponent_direction, "right") == 0)
			params->opponent_direction = ((*new_x = current_x + 1), "down");
		else if (ft_strcmp(params->opponent_direction, "down") == 0)
			params->opponent_direction = ((*new_y = current_y + 1), "left");
		else if (ft_strcmp(params->opponent_direction, "left") == 0)
		{
			params->opponent_direction = ((*new_x = current_x - 1), "up");
		}
		else
			params->opponent_direction = ((*new_y = current_y - 1), "right");
	}
}

void	find_new_position(t_params *params, int *new_x, int *new_y)
{
	int	current_x;
	int	current_y;

	current_x = find_char_x(params->map, 'O');
	current_y = find_char_y(params->map, 'O');
	if (ft_strcmp(params->opponent_direction, "right") == 0)
		*new_x = ((*new_y = current_y), current_x + 1);
	else if (ft_strcmp(params->opponent_direction, "down") == 0)
		*new_x = ((*new_y = current_y + 1), current_x);
	else if (ft_strcmp(params->opponent_direction, "left") == 0)
		*new_x = ((*new_y = current_y), current_x - 1);
	else
		*new_x = ((*new_y = current_y - 1), current_x);
}

void	update_opponent_position(t_params *params)
{
	int			new_x;
	int			new_y;
	int			current_x;
	int			current_y;

	current_x = find_char_x(params->map, 'O');
	current_y = find_char_y(params->map, 'O');
	if (current_x == -1 || current_y == -1)
		return ;
	find_new_position(params, &new_x, &new_y);
	if (new_x == find_char_x(params->map, 'P')
		&& new_y == find_char_y(params->map, 'P'))
		return (mlx_close_window(params->mlx));
	params->opponent_frame = (params->opponent_frame + 1) % 2;
	handle_collision(params, &new_x, &new_y);
	if (params->map[new_y][new_x] != '1' && params->map[new_y][new_x] != 'C'
		&& params->map[new_y][new_x] != 'E')
	{
		draw_file_at(params->mlx, current_x, current_y, "textures/floor.png");
		params->map[current_y][current_x] = '0';
		params->map[new_y][new_x] = 'O';
	}
}

void	update_opponent_sprites(t_params *params)
{
	char		*filename;
	int			x;
	int			y;

	y = find_char_y(params->map, 'O');
	x = find_char_x(params->map, 'O');
	if (y == -1 || x == -1)
		return ;
	draw_file_at(params->mlx, x, y, "textures/floor.png");
	filename = get_sprite_filename("textures/opponent_", 
			params->opponent_direction, params->opponent_frame);
	draw_file_at(params->mlx, x, y, filename);
	free(filename);
}
