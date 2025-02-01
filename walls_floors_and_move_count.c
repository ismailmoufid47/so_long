/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_floors_and_move_count.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:12:58 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/25 14:37:51 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_walls_and_floors(mlx_t *mlx, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_file_at(mlx, j, i, "textures/wall.png");
			else
				draw_file_at(mlx, j, i, "textures/floor.png");
			j++;
		}
		i++;
	}
}

void	print_move_count(t_params *params, int on_screen)
{
	char			*move_count_str;
	char			*move_str;

	ft_printf("\033[H\033[J");
	ft_printf("Move count: %d\n", params->move_count);
	if (!on_screen)
		return ;
	move_count_str = ft_itoa(params->move_count);
	move_str = ft_strjoin("Move count: ", move_count_str);
	free(move_count_str);
	draw_file_at(params->mlx, 0, 0, "textures/counter_background.png");
	mlx_put_string(params->mlx, move_str, 0, 0);
	free(move_str);
}
