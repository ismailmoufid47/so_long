/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:47:50 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/25 15:47:44 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*get_sprite_filename(const char *prefix,
	const char *direction, int frame)
{
	char	*frame_str;
	char	*temp;
	char	*filename;

	frame_str = ft_itoa(frame + 1);
	temp = ft_strjoin(prefix, direction);
	filename = ft_strjoin(temp, "_");
	free(temp);
	temp = filename;
	filename = ft_strjoin(temp, frame_str);
	free(temp);
	free(frame_str);
	temp = filename;
	filename = ft_strjoin(temp, ".png");
	free(temp);
	return (filename);
}

char	*get_filename_and_offset(char map_char,
	int collectible_count, t_params *params)
{
	if (map_char == 'E' && collectible_count != 0)
		return (ft_strdup("textures/door_1.png"));
	else if (map_char == 'C')
		return (ft_strdup("textures/collectible.png"));
	else if (map_char == 'P')
		return (get_sprite_filename("textures/",
				params->character_direction, params->character_frame));
	return (NULL);
}

void	update_sprites(t_params *params)
{
	int				y;
	int				x;
	char			*filename;

	y = 0;
	while (params->map[y])
	{
		x = 0;
		while (params->map[y][x])
		{
			if (params->map[y][x] == 'C' || params->map[y][x] == 'P')
				draw_file_at(params->mlx, x, y, "textures/floor.png");
			filename = get_filename_and_offset(params->map[y][x],
					count_collectibles(params->map), params);
			if (filename)
				draw_file_at(params->mlx, x, y, filename);
			free(filename);
			x++;
		}
		y++;
	}
}
