/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:21:09 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/01 20:27:02 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_params	*params;

	params = (t_params *)param;
	update_character_position(params, keydata);
	update_sprites(params);
	print_move_count(params, 0);
}

int	main(int argc, char **argv)
{
	char		**map;
	mlx_t		*mlx;
	t_params	params;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nUsage: ./so_long map.ber", 2);
		return (1);
	}
	initialize_map(argv[1], &map);
	mlx = mlx_init((CELL_WIDTH * ft_strlen(map[0])),
			(map_height(map) * CELL_HEIGHT), "so_long", false);
	draw_walls_and_floors(mlx, map);
	params = (t_params){mlx, map, 0, 0, "down"};
	update_sprites(&params);
	print_move_count(&params, 0);
	mlx_key_hook(mlx, key_hook, &params);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_map(map, map_height(map));
	return (0);
}
