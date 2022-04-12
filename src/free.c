/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 17:09:11 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/11 21:29:58 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	double_free(char **double_ptr)
{
	int	i;

	i = 0;
	while (double_ptr[i])
	{
		free(double_ptr[i]);
		i++;
	}
	free(double_ptr);
}

void	free_map(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= map->y_len)
	{
		j = -1;
		while (++j < map->x_len)
		{
			free(map->points[i][j]);
		}
		free(map->points[i]);
	}
	free(map->points);
	free(map);
	return ;
}

int	shut_down(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	mlx_loop_end(data->mlx_ptr);
	free(data->mlx_ptr);
	free_map(data->map);
	exit(EXIT_SUCCESS);
	return (0);
}
