/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:20:30 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/29 21:27:36 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_file_at(mlx_t *mlx, int cell_x, int cell_y, char *filename)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;
	int				pixel_x;
	int				pixel_y;

	pixel_x = cell_x * CELL_WIDTH;
	pixel_y = cell_y * CELL_HEIGHT;
	texture = mlx_load_png(filename);
	if (!texture)
	{
		ft_putendl_fd("Error\nFailed to load texture", 2);
		exit(1);
	}
	image = mlx_texture_to_image(mlx, texture);
	if (!image)
	{
		ft_putendl_fd("Error\nFailed to convert texture to image", 2);
		mlx_delete_texture(texture);
		exit(1);
	}
	mlx_image_to_window(mlx, image, pixel_x, pixel_y);
	mlx_delete_texture(texture);
}

void	update_position_and_direction(mlx_key_data_t keydata,
	int *new_x, int *new_y, t_params *params)
{
	if (keydata.key == MLX_KEY_W)
	{
		(*new_y)--;
		params->character_direction = "up";
	}
	else if (keydata.key == MLX_KEY_S)
	{
		(*new_y)++;
		params->character_direction = "down";
	}
	else if (keydata.key == MLX_KEY_A)
	{
		(*new_x)--;
		params->character_direction = "left";
	}
	else if (keydata.key == MLX_KEY_D)
	{
		(*new_x)++;
		params->character_direction = "right";
	}
}

void	handle_special_cases(t_params *params, int new_x,
	int new_y, int collectible_count)
{
	if (params->map[new_y][new_x] == 'E' && collectible_count > 0)
		return ;
	else if ((params->map[new_y][new_x] == 'E' && collectible_count == 0)
		|| params->map[new_y][new_x] == 'O')
		return (mlx_close_window(params->mlx));
}

void	move_character(t_params *params, int new_x, int new_y)
{
	int				char_x;
	int				char_y;

	char_x = find_char_x(params->map, 'P');
	char_y = find_char_y(params->map, 'P');
	if (new_x != char_x || new_y != char_y)
	{
		params->map[char_y][char_x] = '0';
		draw_file_at(params->mlx, char_x, char_y, "textures/floor.png");
		params->map[new_y][new_x] = 'P';
		params->character_frame = (params->character_frame + 1) % 3;
		params->move_count++;
	}
}

void	update_character_position(t_params *params, mlx_key_data_t keydata)
{
	int	char_x;
	int	char_y;
	int	new_x;
	int	new_y;
	int	collectible_count;

	char_y = find_char_y(params->map, 'P');
	char_x = find_char_x(params->map, 'P');
	new_x = char_x;
	new_y = char_y;
	if (keydata.action == MLX_PRESS)
	{
		update_position_and_direction(keydata, &new_x, &new_y, params);
		collectible_count = count_collectibles(params->map);
		if (params->map[new_y][new_x] != '1'
			&& !(collectible_count && params->map[new_y][new_x] == 'E'))
		{
			handle_special_cases(params, new_x, new_y, collectible_count);
			move_character(params, new_x, new_y);
		}
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(params->mlx);
	}
}
