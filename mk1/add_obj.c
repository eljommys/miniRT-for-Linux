/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:47:12 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/18 12:52:45 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

t_sphere	**add_sp(t_sphere **sp, double *O, double r, int c)
{
	t_sphere	**aux;
	int			len;
	int			i;
	int			j;

	len = 0;
	while (sp[len])
		len++;
	if (!(aux = (t_sphere **)malloc(sizeof(t_sphere *) * (len + 2))))
		return (sp);
	i = -1;
	while(++i < len + 1)
	{
		aux[i] = (t_sphere *)malloc(sizeof(t_sphere));
		j = -1;
		if (i < len)
		{
			while (++j < 3)
				aux[i]->O[j] = sp[i]->O[j];
			aux[i]->r = sp[i]->r;
			aux[i]->col = sp[i]->col;
		}
		else
		{
			while (++j < 3)
				aux[i]->O[j] = O[j];
			aux[i]->r = r;
			aux[i]->col = c;
		}
	}
	aux[i] = 0;
	i = 0;
	if (len)
		while (sp[i])
			free(sp[i++]);
	free(sp);
	return (aux);
}

t_light		**add_l(t_light **l, double *O, int c)
{
	t_light		**aux;
	int			len;
	int			i;
	int			j;

	len = 0;
	while (l[len])
		len++;
	if (!(aux = (t_light **)malloc(sizeof(t_light *) * (len + 2))))
		return (l);
	i = -1;
	while(++i < len + 1)
	{
		aux[i] = (t_light *)malloc(sizeof(t_light));
		j = -1;
		if (i < len)
		{
			while (++j < 3)
			{
				aux[i]->O[j] = l[i]->O[j];
				aux[i]->rgb[j] = l[i]->rgb[j];
			}
			aux[i]->col = l[i]->col;
		}
		else
		{
			while (++j < 3)
				aux[i]->O[j] = O[j];
			hex_to_rgb(c, (int *)aux[i]->rgb);
			aux[i]->col = c;
		}
	}
	aux[i] = 0;
	i = 0;
	if (len)
		while (l[i])
			free(l[i++]);
	free(l);
	return (aux);
}

t_plane	**add_pl(t_plane **pl, double *O, double *v, int c)
{
	t_plane		**aux;
	int			len;
	int			i;
	int			j;

	len = 0;
	while (pl[len])
		len++;
	if (!(aux = (t_plane **)malloc(sizeof(t_plane *) * (len + 2))))
		return (pl);
	i = -1;
	while(++i < len + 1)
	{
		aux[i] = (t_plane *)malloc(sizeof(t_plane));
		j = -1;
		if (i < len)
		{
			while (++j < 3)
			{
				aux[i]->O[j] = pl[i]->O[j];
				aux[i]->v[j] = pl[i]->v[j];
			}
			aux[i]->col = pl[i]->col;
		}
		else
		{
			while (++j < 3)
			{
				aux[i]->O[j] = O[j];
				aux[i]->v[j] = v[j];
			}
			aux[i]->col = c;
		}
	}
	aux[i] = 0;
	i = 0;
	if (len)
		while (pl[i])
			free(pl[i++]);
	free(pl);
	return (aux);
}
