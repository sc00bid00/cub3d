/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:14:32 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/16 11:05:50 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/*
	ERR_MEMORY=1,			//"cub3D: error: memory error\n"
	ERR_ARGNUMBER,			//"cub3D: error: wrong arguments number\n"
	ERR_FILENAME,			//"cub3D: error: wrong filename\n"
	ERR_OPENFILE,			//"cub3D: error: file open failure\n"
	ERR_INPUT,				//"cub3D: error: input parameters not ok\n"
	ERR_TEXTURENUMBER,		//"cub3D: error: texture data\n"
	ERR_COLORBYTE,			//"cub3d: error: wrong color input\n",
	ERR_MISSINGCOLORS,		//"cub3d: error: missing color data\n"
	ERR_NOTABLE,			//"cub3D: error: missing map data\n"
	ERR_MAPDATA,			//"cub3D: error: maps contains ivalid data\n"
	ERR_MOREPLAYERS,		//"cub3D: error: more players on the map\n"
	ERR_PLAYERPOSITION,		//"cub3D: error: invalid player position\n"
	ERR_MISSINGPLAYER,		//"cub3D: error: player missing\n"
	ERR_MAPDESIGN			//"cub3D: error: invalid map design\n"
*/

# include <cub3d.h>

typedef enum e_error
{
	ERR_MEMORY=1,
	ERR_ARGNUMBER,
	ERR_FILENAME,
	ERR_OPENFILE,
	ERR_INPUT,
	ERR_TEXTURENUMBER,
	ERR_COLORBYTE,
	ERR_MISSINGCOLORS,
	ERR_NOTABLE,
	ERR_MAPDATA,
	ERR_MOREPLAYERS,
	ERR_PLAYERPOSITION,
	ERR_MISSINGPLAYER,
	ERR_MAPDESIGN
}	error_t;
#endif
