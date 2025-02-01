/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:11:09 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/24 19:04:29 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_characters_and_shape(char **map)
{
	int		i;
	int		j;
	char	valid_chars[6];

	ft_strlcpy(valid_chars, "01CEP", 6);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr(valid_chars, map[i][j]))
				return (0);
			j++;
		}
		if (ft_strlen(map[i]) != ft_strlen(map[0]))
			return (0);
		i++;
	}
	return (1);
}

int	is_closed(char **map)
{
	int	i;
	int	rows;

	rows = 0;
	while (map[rows])
		rows++;
	i = 0;
	while (i < rows)
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	has_required_components(char **map)
{
	int	exit_count;
	int	collectible_count;
	int	start_count;
	int	i;
	int	j;

	exit_count = ((i = 0), (start_count = 0), (collectible_count = 0), 0);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				exit_count++;
			else if (map[i][j] == 'C')
				collectible_count++;
			else if (map[i][j] == 'P')
				start_count++;
			j++;
		}
		i++;
	}
	return (exit_count == 1 && collectible_count >= 1 && start_count == 1);
}

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**duplicate_map(char **map, int rows, int cols)
{
	int		i;
	char	**dup_map;

	dup_map = malloc(sizeof(char *) * (rows + 1));
	if (!dup_map)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		dup_map[i] = malloc(sizeof(char) * (cols + 1));
		if (!dup_map[i])
		{
			free_map(dup_map, i);
			return (NULL);
		}
		ft_strlcpy(dup_map[i], map[i], cols + 1);
		i++;
	}
	dup_map[i] = NULL;
	return (dup_map);
}
