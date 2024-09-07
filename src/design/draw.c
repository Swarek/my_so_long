/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:38:01 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/07 22:04:50 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_xpm_with_transparency(t_vars *vars, int x_pos, int y_pos)
{
	char			*data;
	t_image_info	img;
	t_point			point;
	int				offset_x;
	int				offset_y;

	offset_x = (64 - vars->img_width) / 2;
	offset_y = (64 - vars->img_height) / 2;
	data = mlx_get_data_addr(vars->toprint, &img.bpp,
			&img.size_line, &img.endian);
	point.y = 0;
	while (point.y < vars->img_height)
	{
		point.x = 0;
		while (point.x < vars->img_width)
		{
			point.pixel = *(int *)(data + point.y * img.size_line
					+ point.x * (img.bpp / 8));
			if ((point.pixel & 0x00FFFFFF) != 0x000000)
				mlx_pixel_put(vars->mlx, vars->win, point.x + x_pos + offset_x,
					point.y + y_pos + offset_y, point.pixel);
			point.x++;
		}
		point.y++;
	}
}

void	to_print(t_vars *vars, t_map *map, int x, int y)
{
	if (map->map[y][x] == 'P')
	{
		vars->toprint = vars->player;
		draw_xpm_with_transparency(vars, x * 64, y * 64);
	}
	else if (map->map[y][x] == 'C')
	{
		vars->toprint = vars->collectible;
		draw_xpm_with_transparency(vars, x * 64, y * 64);
	}
	else if (map->map[y][x] == 'E' && map->elems->collectible == 0)
	{
		vars->toprint = vars->exit;
		draw_xpm_with_transparency(vars, x * 64, y * 64);
	}
}

int	draw_map(t_vars *vars, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->width)
	{
		x = 0;
		while (x < map->length)
		{
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->floor, x * 64, y * 64);
			if (map->map[y][x] == '1')
			{
				mlx_put_image_to_window(vars->mlx, vars->win,
					vars->wall, x * 64, y * 64);
			}
			else if (map->map[y][x] == 'P' || map->map[y][x] == 'C'
				|| map->map[y][x == 'E'])
				to_print(vars, map, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
