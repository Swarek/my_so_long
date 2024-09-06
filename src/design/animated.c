/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:53:40 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/06 21:57:38 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Dessiner chaque collectable avec le sprite correspondant à l'animation
// Par exemple : mlx_put_image_to_window(vars->mlx, vars->win,
//				collectable_sprites[sprite_index], x, y);
void	draw_animated_collectables(t_vars *vars, t_map *map)
{
	static int	frame_count;
	int			sprite_index;

	frame_count = 0;
	frame_count++;
	if (frame_count > 10)
	{
		sprite_index = (sprite_index + 1) % NUM_SPRITES;
		frame_count = 0;
	}
}

void	draw_dynamic_elements(t_vars *vars, t_map *map, int pos_x, int pos_y)
{
	draw_player_with_transparency(vars, pos_x, pos_y);
	draw_animated_collectables(vars, map);
}
