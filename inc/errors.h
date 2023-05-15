/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:14:32 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/11 18:17:31 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <cub3d.h>
typedef enum e_error
{
	ERR_MEMORY=1,			//"cub3D: error: memory error\n"
	ERR_ARGNUMBER,			//"cub3D: error: wrong arguments number\n"
	ERR_FILENAME,			//"cub3D: error: wrong filename\n"
	ERR_OPENFILE,			//"cub3D: error: file open failure\n"
	ERR_INPUT,				//"cub3D: error: input parameters not ok\n"
	ERR_TEXTURENUMBER,		//"cub3D: error: texture data\n"
	ERR_COLORBYTE,			//"cub3d: error: wrong color ranges\n"
	ERR_MISSINGCOLORS,		//"cub3d: error: missing color data\n"
	ERR_NOTABLE,			//"cub3D: error: missing map data\n"
	ERR_MAPDATA,			//"cub3D: error: maps contains ivalid data\n"
	ERR_MOREPLAYERS,		//"cub3D: error: more players on the map\n"
	ERR_PLAYERPOSITION,		//"cub3D: error: invalid player position\n"
	ERR_MISSINGPLAYER,		//"cub3D: error: player missing\n"
	ERR_MAPDESIGN			//"cub3D: error: invalid map design\n"
}	error_t;
#endif
