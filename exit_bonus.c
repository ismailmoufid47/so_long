/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:29:22 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/25 15:45:58 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	animate_door(t_params *params)
{
	char			*frame_str;
	char			*door_filename;
	char			*temp;

	frame_str = ft_itoa(params->frame);
	temp = ft_strjoin("textures/door_", frame_str);
	door_filename = ft_strjoin(temp, ".png");
	free(temp);
	free(frame_str);
	draw_file_at(params->mlx, find_char_x(params->map, 'E'),
		find_char_y(params->map, 'E'), door_filename);
	free(door_filename);
}
