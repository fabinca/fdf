/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:43:19 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/16 16:49:37 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	more_keys(int key, t_data *data)
{
	if (key == 'r' || key == 'R')
		data->def_color = RED;
	else if (key == 'g' || key == 'G')
		data->def_color = GREEN;
	else if (key == 'b' || key == 'B')
		data->def_color = BLUE;
	else if (key == 'w' || key == 'W')
		data->def_color = WHITE;
	else if (key == XK_Left)
		data->map->base_x -= 5;
	else if (key == XK_Right)
		data->map->base_x += 5;
	else if (key == XK_Up)
		data->map->base_y -= 5;
	else if (key == XK_Down)
		data->map->base_y += 5;
}

int	handle_keypress(int key, t_data *data)
{
	if (key == XK_Escape)
		shut_down(data);
	else if (key == 'h' || key == 'H')
		data->map->altitude += 1;
	else if ((key == 'f' || key == 'F') && data->map->altitude > 0)
		data->map->altitude -= 1;
	else if (key == 'i' || key == 'I')
		data->map->zoom += 1;
	else if ((key == 'o' || key == 'O') && data->map->zoom > 2)
		data->map->zoom -= 1;
	else if (key == 'X' || key == 'x')
		data->map->angle += 2 * PI / 45;
	else if (key == 'Y' || key == 'y')
		data->map->angle -= 2 * PI / 45;
	else
		more_keys(key, data);
	render(data);
	return (0);
}
