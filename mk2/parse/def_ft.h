/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_ft.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:14:39 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 23:56:46 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_FT_C
# define DEF_FT_C

# include "../raymarching.h"

int	def_p(char *line, int *i, double *P);
int	def_d(char *line, int *i, double *d);
int	def_rgb(char *line, int *i, int *rgb, double alpha);

#endif
