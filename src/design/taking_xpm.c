/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taking_xpm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:37:31 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/07 17:29:50 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	set_img(t_data *data)
// {
// 	data->img.height = 80;
// 	data->img.width = 80;
// 	data->img.floor = "./img/floor_texture.xpm";
// 	data->img.wall = "./img/wall_texture.xpm";
// 	data->img.collect = "./img/collect.xpm";
// 	data->img.player = "./img/zelda.xpm";
// 	data->img.exit = "./img/exit_texture.xpm";
// 	data->img.img_wall = mlx_xpm_file_to_image(data->mlx_ptr, data->img.wall,
// 			&(data->img.width), &(data->img.height));
// 	data->img.img_floor = mlx_xpm_file_to_image(data->mlx_ptr, data->img.floor,
// 			&(data->img.width), &(data->img.height));
// 	data->img.img_exit = mlx_xpm_file_to_image(data->mlx_ptr, data->img.exit,
// 			&(data->img.width), &(data->img.height));
// 	data->img.img_collect = mlx_xpm_file_to_image(data->mlx_ptr,
// 			data->img.collect, &(data->img.width), &(data->img.height));
// 	data->img.img_player = mlx_xpm_file_to_image(data->mlx_ptr,
// 			data->img.player, &(data->img.width), &(data->img.height));
// }

void	destroy_all_images(t_vars *vars)
{
	if (vars->wall)
		mlx_destroy_image(vars->mlx, vars->wall);
	if (vars->floor)
		mlx_destroy_image(vars->mlx, vars->floor);
	if (vars->player)
		mlx_destroy_image(vars->mlx, vars->player);
	if (vars->collectible)
		mlx_destroy_image(vars->mlx, vars->collectible);
	if (vars->exit)
		mlx_destroy_image(vars->mlx, vars->exit);
}

int	set_img(t_vars *vars)
{
	vars->wall = mlx_xpm_file_to_image(vars->mlx, "./img/wall.xpm",
			&vars->img_width, &vars->img_height);
	if (!vars->wall)
		return (destroy_all_images(vars), 1);
	vars->floor = mlx_xpm_file_to_image(vars->mlx, "./img/floor.xpm",
			&vars->img_width, &vars->img_height);
	if (!vars->floor)
		return (destroy_all_images(vars), 1);
	vars->collectible = mlx_xpm_file_to_image(vars->mlx,
			"./img/cold.xpm", &vars->img_width, &vars->img_height);
	if (!vars->collectible)
		return (destroy_all_images(vars), 1);
	vars->exit = mlx_xpm_file_to_image(vars->mlx, "./img/exit.xpm",
			&vars->img_width, &vars->img_height);
	if (!vars->exit)
		return (destroy_all_images(vars), 1);
	vars->player = mlx_xpm_file_to_image(vars->mlx, "./img/cafard.xpm",
			&vars->img_width, &vars->img_height);
	if (!vars->player)
		return (destroy_all_images(vars), 1);
	return (0);
}
