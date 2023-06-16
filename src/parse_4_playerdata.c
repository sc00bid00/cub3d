/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_4_playerdata.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:50:55 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/16 09:32:35 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	get_player(t_pdata *p)
{
	int	i;
	int	j;
	int	player_chk;

	player_chk = 0;
	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (!get_xypostion(&player_chk, p, i, j))
				return (false);
			j++;
		}
		i++;
	}
	if (!player_chk)
		return (put_err(ERR_MISSINGPLAYER), false);
	return (true);
}

bool	get_xypostion(int *player_chk, t_pdata *p, int i, int j)
{
	if (!*player_chk && ft_strchr("NSEW", p->map[i][j]))
	{
		*player_chk = 1;
		p->player_positionxy[0] = j;
		p->player_positionxy[1] = i;
		if (p->player_positionxy[0] == 0 \
			|| p->player_positionxy[0] == p->num_cols - 2 \
			|| p->player_positionxy[1] == 0 \
			|| p->player_positionxy[1] == p->num_rows - 1)
			return (put_err(ERR_PLAYERPOSITION), false);
		get_direction(&p->player_directionrad, p->map[i][j]);
	}
	else if (ft_strchr("NSEW", p->map[i][j]) && player_chk)
		return (put_err(ERR_MOREPLAYERS), false);
	return (true);
}

void	get_direction(double *player_directionrad, char c)
{
	if (c == 'E')
		*player_directionrad = 0;
	else if (c == 'N')
		*player_directionrad = 1.5 * M_PI;
	else if (c == 'W')
		*player_directionrad = M_PI;
	else if (c == 'S')
		*player_directionrad = M_PI_2;
}
