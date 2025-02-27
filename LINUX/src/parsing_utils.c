/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:11:52 by frankgar          #+#    #+#             */
/*   Updated: 2024/12/20 21:16:23 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_fill(char **map, int x, int y, char *pass)
{
	if (!ft_strchr(pass, map[y][x]))
		return (0);
	else if (map[y][x] == '0' && ft_strchr(pass, map[y][x]))
		map[y][x] = 'b';
	else if (map[y][x] == 'E' && ft_strchr(pass, map[y][x]))
		map[y][x] = 's';
	else if (map[y][x] == 'C' && ft_strchr(pass, map[y][x]))
		map[y][x] = 'c';
	else if (map[y][x] == 'b' && ft_strchr(pass, map[y][x]))
		map[y][x] = ' ';
	else if (map[y][x] == 's' && ft_strchr(pass, map[y][x]))
		map[y][x] = 'e';
	map_fill(map, x, y + 1, pass);
	map_fill(map, x + 1, y, pass);
	map_fill(map, x - 1, y, pass);
	map_fill(map, x, y - 1, pass);
	return (1);
}

int	ft_floodfill(char **map, t_player p)
{
	int	y;
	int	x;

	map_fill(map, p.x, p.y, "0EP");
	map_fill(map, p.x, p.y, "bsPC");
	y = 0;
	while (map[y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'E' || map[y][x] == 'C' ||
					map[y][x] == 'o' || map[y][x] == 'C')
				exit(ft_fd_printf(2, "%s", E_IMPOSSIBLE) * 0 + 1);
			else if (map[y][x] == '0')
				map[y][x] = ' ';
		}
		y++;
	}
	map_fill(map, p.x, p.y, "OEPCbso");
	return (1);
}

int	malloc_free_chars(char **tmp_map, int size)
{
	while (size >= 0)
		free (tmp_map[size--]);
	free (tmp_map);
	return (0);
}

int	malloc_free_cases(t_map *map, int size)
{
	while (size >= 0)
		free(map->map[size--]);
	ft_fd_printf(2, "%s", E_MALLOC);
	return (1);
}

int	add_map(t_map *map, char **tmp_map)
{
	int	y;
	int	x;

	y = 0;
	map->map = malloc(map->len * sizeof(char *));
	if (!map->map)
		exit (ft_fd_printf(2, "%s", E_MALLOC) * 0 + 1);
	while (y < map->len)
	{
		x = 0;
		map->map[y] = malloc (map->with * sizeof(char));
		if (!map->map[y])
			exit(malloc_free_cases(map, y));
		while (x < map->with)
		{
			map->map[y][x] = tmp_map[y][x];
			x++;
		}
		y++;
	}
	return (1);
}
