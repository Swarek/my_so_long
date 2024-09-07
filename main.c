/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:49:07 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/07 22:27:53 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_mlx(t_vars *vars)
{
	if (vars->player)
		destroy_all_images(vars);
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_loop_end(vars->mlx);
		mlx_destroy_display(vars->mlx);
		ft_safe_free((void **)&vars->mlx);
	}
	vars->win = NULL;
	vars->player = NULL;
	vars->mlx = NULL;
}

void	free_all(t_vars *vars, t_map *map)
{
	if (vars)
	{
		free_mlx(vars);
		ft_safe_free((void **)&vars);
	}
	if (map)
	{
		if (map->elems)
		{
			free(map->elems);
			map->elems = NULL;
		}
		if (map->map)
			free_all_strings(map->map);
		map->map = NULL;
		ft_safe_free((void **)&map);
	}
}

int	verif_ber(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 1] == 'r' && file[i - 2] == 'e'
		&& file[i - 3] == 'b' && file[i - 4] == '.')
		return (0);
	else
		return (-1);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_vars	*vars;

	if (argc != 2)
		return (ft_error_msg("The program need 1 argument"), -1);
	if (verif_ber(argv[1]) == -1)
		return (ft_error_msg("You need to load a .ber"), -1);
	map = doing_all(argv[1]);
	if (!map)
		return (1);
	ft_print_array(map->map);
	vars = ft_safe_malloc(sizeof(t_vars));
	launch_mlx(vars, map);
	free_all(vars, map);
	return (0);
}
