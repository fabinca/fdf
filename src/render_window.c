/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:44:46 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/16 16:51:17 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	img_p_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x < 0 || y < 0 || x >= W_WIDTH || y >= W_HEIGHT)
		return ;
	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < W_HEIGHT)
	{
		j = 0;
		while (j < W_WIDTH)
		{
			if (i < 10 || j < 10 || i > W_HEIGHT - 10 || j > W_WIDTH - 10)
				img_p_put(img, j++, i, color);
			else
				img_p_put(img, j++, i, BLACK);
		}
		++i;
	}
}

static void	render_text(void *mlx_ptr, void *win_ptr, char *name, int color)
{
	mlx_string_put(mlx_ptr, win_ptr, 20, 25, color, \
	"FDF Project by cfabian");
	mlx_string_put(mlx_ptr, win_ptr, 20, 45, color, \
	name);
	mlx_string_put(mlx_ptr, win_ptr, 20, 60, color, \
	"Press [G]reen [B]lue [R]ed [W]hite to change the color");
	mlx_string_put(mlx_ptr, win_ptr, 20, 75, color, \
	"Press arrows to move the map");
	mlx_string_put(mlx_ptr, win_ptr, 20, 90, color, \
	"Press [O]ut and [I]n to zoom");
	mlx_string_put(mlx_ptr, win_ptr, 20, 105, color, \
	"Press [H]igher or [F]latter to change altitude");
	mlx_string_put(mlx_ptr, win_ptr, 20, 120, color, \
	"Press [Y] or [X] to rotate");
}

int	render(t_data *d)
{
	void	*old_image;

	if (d->win_ptr == NULL)
		return (1);
	old_image = d->img.mlx_img;
	d->img.mlx_img = mlx_new_image(d->mlx_ptr, W_WIDTH, W_HEIGHT);
	d->img.addr = mlx_get_data_addr(d->img.mlx_img, &d->img.bpp,
			&d->img.line_len, &d->img.endian);
	render_background(&d->img, d->def_color);
	render_map(d->map, *d);
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img.mlx_img, 0, 0);
	render_text(d->mlx_ptr, d->win_ptr, d->name, d->def_color);
	mlx_destroy_image(d->mlx_ptr, old_image);
	return (0);
}
