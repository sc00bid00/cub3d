/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:52:20 by lsordo            #+#    #+#             */
/*   Updated: 2023/06/16 09:59:30 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <cub3d.h>
# include <stdbool.h>

typedef struct s_display	t_display;
typedef struct s_pdata		t_pdata;

/* FUNCTIONS */

/*	UTILS_FREE */
void	ft_freesplit_2(char **arr, int n);
void	ft_freesplit(char **arr);
void	tmp_freelst(t_list *lst);
void	tmp_freearr(char **arr);
void	tmp_freedisplay(t_display *d);
/*	UTILS_PRINT */
void	tmp_prtlst(t_list *lst);
void	tmp_prtarr(char **arr);

#endif
