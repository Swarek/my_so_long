/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:02:00 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/07 22:05:42 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	player_horizontal_mov(char **map, int direction, t_elements *elems)
{
	int	row;
	int	col;

	searching_char(map, 'P', &row, &col);
	if (map[row][col + direction / 2] == 'C')
		elems->collectible--;
	if (map[row][col + direction / 2] == 'E'
		&& elems->collectible == 0)
		return (1);
	if (map[row][col + direction / 2] == '0'
		|| map[row][col + direction / 2] == 'C')
	{
		map[row][col] = '0';
		map[row][col + direction / 2] = 'P';
		return (0);
	}
	return (-1);
}

int	player_vertical_mov(char **map, int direction, t_elements *elems)
{
	int	row;
	int	col;

	searching_char(map, 'P', &row, &col);
	if (map[row + direction][col] == 'C')
		elems->collectible--;
	if (map[row + direction][col] == 'E'
		&& elems->collectible == 0)
		return (1);
	if (map[row + direction][col] == '0'
		|| map[row + direction][col] == 'C')
	{
		map[row][col] = '0';
		map[row + direction][col] = 'P';
		return (0);
	}
	return (-1);
}

int	player_movement(char **map, int direction, t_elements *elems)
{
	if (direction == TOP || direction == BOTTOM)
		return (player_vertical_mov(map, direction, elems));
	if (direction == LEFT || direction == RIGHT)
		return (player_horizontal_mov(map, direction, elems));
	return (0);
}
