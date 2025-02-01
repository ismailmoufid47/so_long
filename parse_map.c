/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:28:58 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/01 20:40:02 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	explore(t_map_state *state, int x, int y)
{
	if (x < 0 || x >= state->cols || y < 0 || y >= state->rows
		|| state->map[y][x] == '1' || state->map[y][x] == 'F')
		return ;
	if (state->map[y][x] == 'C')
		state->collectibles--;
	if (state->map[y][x] == 'E')
	{
		state->exit_found = 1;
		return ;
	}
	state->map[y][x] = 'F';
	explore(state, x + 1, y);
	explore(state, x - 1, y);
	explore(state, x, y + 1);
	explore(state, x, y - 1);
}

int	has_valid_path(char **map)
{
	t_map_state	state;
	int			start_x;
	int			start_y;

	state = (t_map_state){map, map_height(map), ft_strlen(map[0]), 0, 0};
	state.map = duplicate_map(map, state.rows, state.cols);
	state.collectibles = count_collectibles(state.map);
	if (!state.map)
		return (0);
	start_x = find_char_x(state.map, 'P');
	start_y = find_char_y(state.map, 'P');
	explore(&state, start_x, start_y);
	free_map(state.map, state.rows);
	return (state.collectibles == 0 && state.exit_found);
}

int	count_lines(const char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error\nFailed to open map file", 2);
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	if (lines == 0)
	{
		ft_putendl_fd("Error\nEmpty map file", 2);
		exit(1);
	}
	close(fd);
	return (lines);
}

int	fill_map(int fd, char **map)
{
	char	*line;
	char	**split;
	int		i;

	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		split = ft_split(line, '\n');
		if (!split || !split[0])
		{
			ft_putendl_fd("Error\nEmpty line", 2);
			free(line);
			exit(1);
		}
		map[i] = split[0];
		free(split[1]);
		free(split);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (i);
}

char	**parse_map(const char *filename)
{
	int		fd;
	char	**map;

	if (!ft_strrchr(filename, '.')
		|| (ft_strrchr(filename, '.')
			&& ft_strncmp(ft_strrchr(filename, '.'), ".ber", 4) != 0)
		|| (ft_strrchr(filename, '.') == filename)
		|| (ft_strrchr(filename, '/')
			&& ft_strrchr(filename, '/') + 1 == ft_strrchr(filename, '.')))
	{
		ft_putendl_fd("Error\nInvalid map file", 2);
		exit(1);
	}
	map = (malloc(sizeof(char *) * (count_lines(filename) + 1)));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		ft_putendl_fd("Error\nFailed to open map file", 2);
		exit(1);
	}
	return (fill_map(fd, map), close(fd), map);
}
