/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 10:58:20 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/05 14:02:46 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIST_H
# define DIST_H

# include "../raymarching.h"

double	sp_dist(t_data *param);
double	pl_dist(t_data *param);
double	sq_dist(t_data *param);
double	bx_dist(t_data *param);
double	cy_dist(t_data *param);
double	tr_dist(t_data *param);

#endif
