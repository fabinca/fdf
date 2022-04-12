/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:18:04 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/16 16:51:07 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/* reads lines from fd and stores them as a linked list (one entry per line) */
static t_list	*fd_to_list(int fd, t_map *map)
{
	t_list	*line;
	t_list	*start;
	int		line_ct;

	start = NULL;
	line_ct = 0;
	while (1)
	{
		line = ft_lstnew(get_next_line(fd));
		if (!line->content)
			break ;
		if (!start)
			start = line;
		else
			ft_lstadd_back(&start, line);
		line_ct++;
	}
	ft_lstdelone(line, *free);
	map->y_len = line_ct - 1;
	return (start);
}

/*making points by atoiing info & update z_min & z_max in map*/
static t_point	*new_point(char *z, char *color)
{
	t_point	*point;

	point = (t_point *)malloc(sizeof(t_point));
	if (color)
		point->color = ft_atoi_base(color, "0123456789ABCDEF");
	else
		point->color = 0;
	point->z = ft_atoi(z);
	return (point);
}

/*splits line by space and then by ','(for color) to make points of row */
t_point	**line_to_row(char *line, t_map *map)
{
	char	**split;
	char	**z_color_split;
	int		col;
	t_point	**row;

	col = -1;
	row = (t_point **)ft_calloc(map->x_len + 1, sizeof(t_point *));
	split = ft_split(line, ' ');
	while (++col < map->x_len)
	{
		z_color_split = ft_split(split[col], ',');
		row[col] = new_point(z_color_split[0], z_color_split[1]);
		double_free(z_color_split);
	}
	double_free(split);
	return (row);
}

int	list_to_map(t_list *lines, t_map *map)
{
	int		row;
	t_list	*tmp;

	map->points = (t_point ***)ft_calloc(map->y_len + 1, sizeof(t_point **));
	row = -1;
	while (lines && ++row <= map->y_len)
	{
		map->points[row] = line_to_row(lines->content, map);
		tmp = lines->next;
		ft_lstdelone(lines, *free);
		lines = tmp;
	}
	return (1);
}

t_map	*read_map(int fd)
{
	t_map	*map;
	t_list	*lines;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->base_x = W_WIDTH / 2;
	map->base_y = 50;
	map->zoom = 30;
	map->altitude = 1;
	map->angle = PI / 4;
	lines = fd_to_list(fd, map);
	map->x_len = ft_nb_parts(lines->content, ' ') - 1;
	if (!list_to_map(lines, map))
		return (NULL);
	return (map);
}
