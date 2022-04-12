/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:35:39 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/09 17:04:41 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	translate(char *str, char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != 0)
	{
		while (base[j] != 0)
		{
			if (str[i] == base[j])
			{
				str[i] = '0' + j;
				break ;
			}
			j++;
		}
		i++;
	}
}

int	ft_atoi_base(char *str, char *base)
{
	int	num;
	int	negative_ct;
	int	basenum;

	num = 0;
	negative_ct = 0;
	basenum = ft_strlen(base);
	while (ft_isspace(str[0]))
		str++;
	if (*str == '0' && *(str + 1) == 'x')
		str += 2;
	translate(str, base);
	while (*str >= '0' && *str <= '0' + basenum)
	{
		num = num * basenum + (*str - '0');
		str++;
	}
	if (negative_ct % 2 == 1)
		num = num * -1;
	return (num);
}
