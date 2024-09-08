/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:28:37 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/08 16:54:46 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	where_start_flood(char **map)
{
	int		row;
	int		col;
	int		result;
	char	**cpy_map;

	row = 0;
	col = 0;
	cpy_map = array_strcpy(map);
	searching_char(map, 'P', &row, &col);
	if (flood_fill(cpy_map, row, col) == -1)
		return (ft_2dclear(cpy_map), ft_error_msg("Exit not accessible"));
	result = verif_flood(cpy_map);
	if (result == -1)
		return (free_all_strings(cpy_map), -1);
	ft_2dclear(cpy_map);
	return (result);
}

int	flood_fill(char **map, int row, int col)
{
	int	result;

	if (row < 0 || row > ft_strlen_2d(map) || col < 0
		|| col > (int)ft_strlen(map[0]))
		return (-1);
	if (map[row][col] == 'E')
		return (0);
	if (map[row][col] == '1' || map[row][col] == '2')
		return (1);
	if (map[row][col] == '0' || map[row][col] == 'C' || map[row][col] == 'P')
		map[row][col] = '2';
	result = 1;
	if (flood_fill(map, row - 1, col) == 0)
		result = 0;
	if (flood_fill(map, row + 1, col) == 0)
		result = 0;
	if (flood_fill(map, row, col - 1) == 0)
		result = 0;
	if (flood_fill(map, row, col + 1) == 0)
		result = 0;
	return (result);
}

int	verif_flood(char **flooded)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (flooded[i] != NULL)
	{
		while (flooded[i][j] != '\0')
		{
			if (flooded[i][j] == '0' || flooded[i][j] == 'C'
				|| flooded[i][j] == 'P')
				return (ft_error_msg("Intouchable empty"));
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}
