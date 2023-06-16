/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:35:19 by kczichow          #+#    #+#             */
/*   Updated: 2023/06/16 10:59:55 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

// bool check_other_input(char *str)
// {
// 	int i;

// 	i = 0;
// 	if (str[i] == "\0")
// 		return (TRUE);
// 	else
// 		return ()
	
// }
bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (TRUE)
	else
		return (FALSE);
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
		if ((number * sign) < INT32_MIN)
			return (0);
		else if ((number * sign) > INT32_MAX)
			return (-1);
		number = number * 10 + str[i++] - '0';
	}
	while (str[i] && is_whitespace(str[i]))
		i++;
	if (str[i])
		return (-1);
	return ((int)(number * sign));
}
