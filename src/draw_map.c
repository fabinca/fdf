/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:04:02 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/16 16:52:32 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	get_coors(int point[3], int x, int y, t_data d)
{
	point[0] = d.map->base_x + (x * cos(d.map->angle) - y * sin(d.map->angle)) \
	* d.map->zoom * sin(PI / 3) / sin(PI / 2);
	point[1] = d.map->base_y + (x * sin(d.map->angle) + y * cos(d.map->angle)) \
	* d.map->zoom * sin(PI / 6) / sin(PI / 2) \
	- (d.map->points[y][x]->z * d.map->altitude * d.map->zoom / 10);
	point[2] = d.map->points[y][x]->color;
	if (point[2] == 0)
		point[2] = d.def_color;
	return (1);
}

static void	draw_line(int f[3], int t[3], t_data d)
{
	const int	dist_x = abs(f[0] - t[0]);
	const int	dist_y = abs(f[1] - t[1]);
	int			i;
	float		j[3];

	i = 0;
	j[0] = 1;
	j[1] = 1;
	j[2] = 0;
	if (dist_x < dist_y)
		j[0] = (float) dist_x / dist_y;
	else if (dist_y < dist_x)
		j[1] = (float) dist_y / dist_x;
	if (f[0] > t[0])
		j[0] *= -1;
	if (f[1] > t[1])
		j[1] *= -1;
	while ((f[0] > t[0] && f[0] + (i * j[0]) >= t[0]) || \
		(f[0] < t[0] && f[0] + (i * j[0]) <= t[0]) || \
		(f[0] == t[0] && f[1] + (i * j[1]) != t[1]))
	{
		img_p_put(&d.img, f[0] + (int)(i * j[0]), f[1] + (int)(i * j[1]), f[2]);
		if (abs((int)((i++) * j[0])) >= dist_x / 2)
			f[2] = t[2];
	}
}

void	render_map(t_map *map, t_data d)
{
	int	from[3];
	int	to[3];
	int	x;
	int	y;

	x = 0;
	while (++x <= map->x_len)
	{
		y = 0;
		while (++y <= map->y_len)
		{
			if (get_coors(from, x - 1, y - 1, d) && get_coors(to, x - 1, y, d))
				draw_line(from, to, d);
			if (x == map->x_len)
				continue ;
			if (get_coors(from, x - 1, y - 1, d) && get_coors(to, x, y - 1, d))
				draw_line(from, to, d);
		}
		if (x == map->x_len)
			continue ;
		if (get_coors(from, x - 1, map->y_len, d) \
			&& get_coors(to, x, map->y_len, d))
			draw_line(from, to, d);
	}
	return ;
}
