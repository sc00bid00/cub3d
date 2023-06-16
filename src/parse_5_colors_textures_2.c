/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_5_colors_textures_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:37:10 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/16 11:19:31 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (true);
	else
		return (false);
}

int	check_sign(char c)
{
	int	sign;

	sign = 1;
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = sign * (-1);
	}
	return (sign);
}

int	ft_atoi_m(const char *str)
{
	int		i;
	long	sign;
	long	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] != '\0' && is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = sign * (-1);
	}
	while (ft_isdigit(str[i]) == 1)
	{
		if ((number * sign) < INT32_MIN || (number * sign) > INT32_MAX)
			return (-1);
		number = number * 10 + str[i++] - '0';
	}
	while (str[i] && is_whitespace(str[i]))
		i++;
	if (str[i])
		return (-1);
	return ((int)(number * sign));
}

int	get_arrsize(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

bool	chk_colorsdata(t_pdata *p)
{
	int		i[2];
	int		colors[3];
	char	**arr;
	int		n;

	i[0] = 0;
	while (p->color_string && p->color_string[i[0]])
	{
		arr = ft_split(p->color_string[i[0]], ',');
		if (get_arrsize(arr) != 3)
			return (ft_freesplit(arr), put_err(ERR_INPUT));
		i[1] = 0;
		while (arr && arr[i[1]])
		{
			n = ft_atoi_m(arr[i[1]]);
			if (n < 0 || n > 255)
				return (ft_freesplit(arr), put_err(ERR_COLORBYTE));
			else
				colors[i[1]++] = n;
		}
		p->colors_fc[i[0]] = get_rgba(colors[0], colors[1], colors[2]);
		ft_freesplit(arr);
		i[0]++;
	}
	return (true);
}
