/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:14:32 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/05 19:47:29 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
typedef enum e_error
{
	ERR=1,
	ERR_NARG,
	ERR_NAME,
	ERR_OPEN,
	ERR_NTEX,
	ERR_PTEX
}	error_t;
#endif
