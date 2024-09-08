/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:18:27 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/08 15:12:21 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_hook(int keycode, t_data *data)
{
	t_map	*map;
	t_vars	*vars;

	map = data->map;
	vars = data->vars;
	if (!vars || !map || !map->map)
		return (ft_error_msg("Error: Invalid pointers passed to key_hook\n"));
	if (keycode == KEY_ESC)
	{
		if (vars->win && vars->mlx)
		{
			free_all(vars, map);
			exit(0);
		}
		else
			return (ft_error_msg("Error: Window or mlx not initialized\n"));
	}
	hook_movements(keycode, data);
	return (0);
}

void	hook_movements(int keycode, t_data *data)
{
	int	movement;

	movement = -1;
	if (keycode == KEY_W || keycode == KEY_UP)
		movement = player_movement(data->map->map, TOP, data->map->elems);
	if (keycode == KEY_A || keycode == KEY_LEFT)
		movement = player_movement(data->map->map, LEFT, data->map->elems);
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		movement = player_movement(data->map->map, RIGHT, data->map->elems);
	if (keycode == KEY_S || keycode == KEY_DOWN)
		movement = player_movement(data->map->map, BOTTOM, data->map->elems);
	if (movement == 1)
	{
		data->map->count++;
		ft_printf("\n\n\n\n\n\n\n\n\n\n\nYou win !!!!!!!!!!!!!!!!\n");
		ft_printf("Total Count : %d", data->map->count);
		free_all(data->vars, data->map);
		exit(1);
	}
	else if (movement == 0)
	{
		data->map->count++;
		ft_printf("Count : %d\n", data->map->count);
	}
}
