/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:08:08 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/07 22:45:22 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	start_open_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		ft_error_msg("Error: mlx_init failed\n");
		return (1);
	}
	vars->win = mlx_new_window(vars->mlx, 1920, 1080, "SO_LONG");
	if (!vars->win)
	{
		ft_error_msg("Error: mlx_new_window failed\n");
		return (1);
	}
	return (0);
}

int	close_window(t_data *data)
{
	free_all(data->vars, data->map);
	exit(0);
}

int	update(t_data *data)
{
	char	*val_str;
	t_vars	*vars;

	vars = data->vars;
	if (data->vars->win)
	{
		mlx_clear_window(data->vars->mlx, data->vars->win);
		draw_map(data->vars, data->map);
		val_str = ft_itoa(data->map->count);
		mlx_string_put(vars->mlx, vars->win, 100, 50, 0xFF0000, val_str);
		mlx_string_put(vars->mlx, vars->win, 101, 50, 0xFF0000, val_str);
		mlx_string_put(vars->mlx, vars->win, 100, 51, 0xFF0000, val_str);
		mlx_string_put(vars->mlx, vars->win, 101, 51, 0xFF0000, val_str);
		free(val_str);
		return (0);
	}
	else
		return (1);
}

int	mlx_looping(t_data *data)
{
	if (!data->vars->win || !data->vars->mlx)
	{
		ft_error_msg("Error: mlx or window not initialized\n");
		return (1);
	}
	mlx_key_hook(data->vars->win, key_hook, data);
	mlx_loop_hook(data->vars->mlx, update, data);
	mlx_hook(data->vars->win, 17, 0, close_window, data);
	mlx_loop(data->vars->mlx);
	return (0);
}

int	launch_mlx(t_vars *vars, t_map *map)
{
	t_data	data;

	data.map = map;
	data.vars = vars;
	if (start_open_window(vars) != 0)
		return (ft_error_msg("Error: Failed to open window\n"), 1);
	set_img(vars);
	if (draw_map(vars, map) != 0)
		return (ft_error_msg("Error: Failed to draw map\n"), 1);
	if (mlx_looping(&data) != 0)
		return (ft_error_msg("Error: mlx_loop failed\n"), 1);
	return (0);
}
