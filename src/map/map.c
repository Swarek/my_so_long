/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:24 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/08 17:33:55 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	del_nl(char **map)
{
	int		i;
	int		len;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > 0 && map[i][len - 1] == '\n' && map[i + 1])
			map[i][len - 1] = '\0';
		i++;
	}
}

char	**get_map(char *path)
{
	char	**map;
	char	*line;
	int		fd;
	int		i;

	fd = open(path, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	map = ft_safe_malloc((i + 1) * sizeof(char *));
	close (fd);
	fd = open(path, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map[i++] = line;
		line = get_next_line(fd);
	}
	return (close (fd), map[i] = NULL, del_nl(map), map);
}

t_map	*doing_all(char	*path)
{
	t_elements	*elements;
	t_map		*map;

	map = ft_safe_malloc(sizeof(t_map));
	elements = ft_safe_malloc(sizeof(t_elements));
	ft_memset(elements, 0, sizeof(t_elements));
	ft_memset(map, 0, sizeof(t_map));
	map->map = get_map(path);
	map->elems = elements;
	if (!map->map)
		return (free_all(NULL, map), NULL);
	if (parse_the_map(map, elements) == -1)
		return (free_all(NULL, map), NULL);
	if (where_start_flood(map->map) == -1)
		return (free_all(NULL, map), NULL);
	if (map_closed(map->map) == -1)
		return (free_all(NULL, map), NULL);
	if (map->elems->collectible == 0)
		return (ft_error_msg("No collectible"), free_all(NULL, map), NULL);
	map->count = 0;
	return (map);
}
