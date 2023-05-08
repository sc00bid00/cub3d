/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:14:32 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/08 19:27:36 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <cub3d.h>
typedef enum e_error
{
	ERR=1,
	ERR_NARG,
	ERR_NAME,
	ERR_OPEN,
	ERR_NTEX,
	ERR_MTEX,
	ERR_PTEX,
	ERR_COLS,
	ERR_FLCL,
	ERR_NTBL,
	ERR_NALL
}	error_t;
#endif
