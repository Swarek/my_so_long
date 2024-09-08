/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:49:07 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/08 16:55:15 by mblanc           ###   ########.fr       */
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

int	free_all(t_vars *vars, t_map *map)
{
	if (vars)
	{
		free_mlx(vars);
		ft_safe_free((void **)&vars);
	}
	if (map)
	{
		// if (map->elems)
		// {
		// 	free(map->elems);
		// 	map->elems = NULL;
		// }
		ft_safe_free((void **)&map->elems);
		if (map->map)
			free_all_strings(map->map);
		map->map = NULL;
		ft_safe_free((void **)&map);
	}
	exit(0);
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

int	test_file(char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	if (line == NULL)
		return (ft_safe_free((void **)&line), close(fd), -1);
	else
		return (ft_safe_free((void **)&line), close(fd), 0);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_vars	*vars;

	if (argc != 2)
		return (ft_error_msg("The program need 1 argument"), -1);
	if (verif_ber(argv[1]) == -1)
		return (ft_error_msg("You need to load a .ber"), -1);
	if (test_file(argv[1]) == -1)
		return (ft_error_msg("Problem opening the map"), -1);
	map = doing_all(argv[1]);
	if (!map)
		return (-1);
	vars = ft_safe_malloc(sizeof(t_vars));
	launch_mlx(vars, map);
	free_all(vars, map);
	return (0);
}
