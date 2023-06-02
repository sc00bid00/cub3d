/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_6_other_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:39:38 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/02 14:51:17 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	chk_empty(char *str)
{
	while (str && *str)
	{
		if (*str++ > 32)
			return (false);
	}
	return (true);
}

bool	chk_valid(t_list *tmp, int *chk)
{
	char	*dum;
	int		flag;
	char	*test;

	dum = NULL;
	test = "NSWEFC";
	while (tmp)
	{
		flag = 0b000000;
		if (tmp->content)
			dum = ft_strtrim(tmp->content, " \t");
		if (dum && !ft_strchr(test, dum[0]) && !ft_strchr("01", dum[0]))
			return (free(dum), false);
		else if (!ft_strchr("01", dum[0]))
		{
			flag |= 1 << (ft_strchr(test, dum[0]) - test);
			if (flag & *chk)
				return (free(dum), false);
			*chk |= flag;
		}
		if (dum)
			free(dum);
		tmp = tmp->next;
	}
	return (true);
}

bool	chk_data(t_pdata *p)
{
	t_list	*tmp;
	int		chk;

	tmp = p->file_data;
	chk = 0b000000;
	if (!chk_valid(tmp, &chk) || chk != 0b111111)
		return (put_err(ERR_INPUT));
	return (true);
}

bool	chk_rows(t_pdata *p)
{
	int	i;
	int	j;

	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (!ft_strchr(" 01NSEW\n", p->map[i][j]))
				return (put_err(ERR_MAPDATA), false);
			j++;
		}
		i++;
	}
	return (true);
}
