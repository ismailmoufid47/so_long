/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:58:56 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/29 21:47:07 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	find_char_y(char **map, char c)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int	find_char_x(char **map, char c)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				return (j);
			j++;
		}
		i++;
	}
	return (-1);
}

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	count_collectibles(char **map)
{
	int	collectible_count;
	int	y;
	int	x;

	collectible_count = 0;
	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'C')
				collectible_count++;
			x++;
		}
		y++;
	}
	return (collectible_count);
}

void	initialize_map(char *filename, char ***map)
{
	*map = parse_map(filename);
	if (!*map
		|| !is_valid_characters_and_shape(*map)
		|| !is_closed(*map)
		|| !has_required_components(*map)
		|| !has_valid_path(*map))
	{
		ft_putendl_fd("Error\nInvalid map", 2);
		free_map(*map, count_lines(filename));
		exit(1);
	}
}
