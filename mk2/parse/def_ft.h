/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_ft.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:14:39 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/05 13:57:29 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_FT_H
# define DEF_FT_H

# include "../raymarching.h"

int	def_p(char *line, int *i, double *p);
int	def_d(char *line, int *i, double *d);
int	def_rgb(char *line, int *i, int *rgb, double alpha);

#endif
