/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:51:37 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/16 16:53:20 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

# define W_NAME "FDF by Carlotta Fabian"
# define W_WIDTH 1200
# define W_HEIGHT 600
# define BLACK 0x000000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define RED 0xFF0000
# define WHITE 0xFFFFFF
# define PI 3.14159265358979323846

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_point
{
	int		z;
	int		color;
}	t_point;

typedef struct s_map
{
	int		x_len;
	int		y_len;
	int		z_max;
	int		z_min;
	int		base_x;
	int		base_y;
	int		altitude;
	int		zoom;
	float	angle;
	t_point	***points;
}	t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*name;
	int		cur_img;
	int		def_color;
	t_img	img;
	t_map	*map;
}	t_data;

t_map	*read_map(int fd);
void	img_p_put(t_img *img, int x, int y, int color);
void	render_map(t_map *map, t_data d);
void	free_map(t_map *map);
void	double_free(char **double_ptr);
int		shut_down(t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		render(t_data *data);

#endif