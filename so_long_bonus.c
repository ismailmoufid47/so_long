/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:21:09 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/01 20:26:58 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_params	*params;

	params = (t_params *)param;
	update_character_position(params, keydata);
	update_sprites(params);
	print_move_count(params, 1);
}

void	loop_hook(void *param)
{
	t_params	*params;

	params = (t_params *)param;
	if (params->frame_counter == 10)
	{
		update_opponent_position(params);
		update_opponent_sprites(params);
		if (count_collectibles(params->map) == 0)
		{
			if (params->frame < 7)
				params->frame++;
			animate_door(params);
		}
		params->frame_counter = 0;
	}
	params->frame_counter++;
}

int	main(int argc, char **argv)
{
	char		**map;
	mlx_t		*mlx;
	t_params	params;

	if (argc != 2)
	{
		ft_putendl_fd("Erorr\nUsage: ./so_long map.ber", 2);
		return (1);
	}
	initialize_map(argv[1], &map);
	mlx = mlx_init((CELL_WIDTH * ft_strlen(map[0])),
			(map_height(map) * CELL_HEIGHT), "so_long", false);
	draw_walls_and_floors(mlx, map);
	add_opponent_to_map(map);
	params = (t_params){mlx, map, 0, 0, "down", 0, "down", 0, 0};
	update_sprites(&params);
	print_move_count(&params, 1);
	mlx_key_hook(mlx, key_hook, &params);
	mlx_loop_hook(mlx, loop_hook, &params);
	mlx_loop(mlx);
	free_map(map, map_height(map));
	mlx_terminate(mlx);
	return (0);
}
