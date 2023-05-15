/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:52:20 by lsordo            #+#    #+#             */
/*   Updated: 2023/05/15 13:46:59 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <cub3d.h>
# include <stdbool.h>

typedef struct s_display t_display;
typedef struct s_pdata t_pdata;

// ====== utils_debug ======
void	tmp_prtlst(t_list *lst);
void	tmp_prtarr(char **arr);
void	tmp_freelst(t_list *lst);
void	tmp_freearr(char **arr);
void	tmp_freedisplay(t_display *d);

void	ft_freesplit(char **arr);
void	ft_freesplit_2(char **arr, int n);

bool	put_err(error_t ERR_NUM);
bool	init_pdata(t_display *d, char **argv);
bool	get_data(t_pdata *p);
bool	chk_args(int argc, char **argv);

#endif
