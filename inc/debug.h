/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:52:20 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/05 20:40:42 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <cub3d.h>

// ====== utils_debug ======
void	tmp_prtlst(t_list *lst);
void	tmp_prtarr(char **arr);
void	tmp_freelst(t_list **lst);
void	tmp_freearr(char ***arr);
void	tmp_freedisplay(t_display *d);
#endif
