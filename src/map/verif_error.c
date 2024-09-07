/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:37:07 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/07 22:16:24 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	only_ones(char *str)
{
	if (!str || *str == '\0')
		return (-1);
	while (*str)
	{
		if (*str != '1')
			return (-1);
		str++;
	}
	return (0);
}

int	first_end_ones(char *str)
{
	if (!str || *str == '\0')
		return (-1);
	if (*str != '1')
		return (-1);
	while (*str)
		str++;
	str--;
	if (*str != '1')
		return (-1);
	return (0);
}

int	map_closed(char **map)
{
	int	i;

	i = 0;
	if (only_ones(map[0]) == -1)
		return (ft_error_msg("Map not closed"), -1);
	while (map[i] != NULL)
		if (first_end_ones(map[i++]) == -1)
			return (ft_error_msg("Map not closed"), -1);
	if (only_ones(map[i - 1]) == -1)
		return (ft_error_msg("Map not closed"), -1);
	return (0);
}

int	elems_on_the_line(char *line, t_elements *count_elems)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '0')
			count_elems->empty++;
		else if (line[i] == '1')
			count_elems->wall++;
		else if (line[i] == 'C')
			count_elems->collectible++;
		else if (line[i] == 'E')
			count_elems->map_exit++;
		else if (line[i] == 'P')
			count_elems->starting_pos++;
		else
			return (0);
		i++;
	}
	return (0);
}

int	parse_the_map(t_map *map, t_elements *count_elems)
{
	int	i;

	i = 0;
	map->length = ft_strlen(map->map[0]);
	if (map->length > 31)
		return (ft_error_msg("Map too long\n"), 1);
	while (map->map[i])
	{
		if (map->length != (int)ft_strlen(map->map[i]))
			return (ft_error_msg("Not rectangular / Too much newlines\n"), 1);
		if (elems_on_the_line(map->map[i], count_elems))
			return (ft_error_msg("Not good count of elems\n"), 1);
		i++;
	}
	map->width = i;
	if (map->width > 16)
		return (ft_error_msg("Map too large\n"), 1);
	if (count_elems->starting_pos != 1 || count_elems->map_exit != 1
		|| count_elems->collectible == 0)
		return (ft_printf("Problem elements count on map\n"), 1);
	return (0);
}
