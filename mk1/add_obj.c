/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:47:12 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/24 12:57:50 by jserrano         ###   ########.fr       */
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
	double		Vn[3];
	int			len;
	int			i;
	int			j;

	len = 0;
	while (pl[len])
		len++;
	if (!(aux = (t_plane **)malloc(sizeof(t_plane *) * (len + 2))))
		return (pl);
	i = -1;
	while (++i < 3)
		Vn[i] = v[i] / mod(v);
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
				aux[i]->v[j] = Vn[j];
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

t_square	**add_sq(t_square **sq, double *O, double *v, double h, int c)
{
	t_square	**aux;
	double		Vn[3];
	int			len;
	int			i;
	int			j;

	len = 0;
	while (sq[len])
		len++;
	if (!(aux = (t_square **)malloc(sizeof(t_square *) * (len + 2))))
		return (sq);
	i = -1;
	while (++i < 3)
		Vn[i] = v[i] / mod(v);
	i = -1;
	while(++i < len + 1)
	{
		aux[i] = (t_square *)malloc(sizeof(t_square));
		j = -1;
		if (i < len)
		{
			while (++j < 3)
			{
				aux[i]->O[j] = sq[i]->O[j];
				aux[i]->v[j] = sq[i]->v[j];
				aux[i]->x[j] = sq[i]->x[j];
				aux[i]->y[j] = sq[i]->y[j];
			}
			aux[i]->h = sq[i]->h;
			aux[i]->col = sq[i]->col;
		}
		else
		{
			while (++j < 3)
			{
				aux[i]->O[j] = O[j];
				aux[i]->v[j] = Vn[j];
			}
			aux[i]->x[0] = 0;
			aux[i]->x[1] = -Vn[2];
			aux[i]->x[2] = Vn[1];
			j = -1;
			while (++j < 3)
				aux[i]->y[j] = cross_prod(Vn, aux[i]->x, j);
			j = -1;
			while (++j < 3)
				aux[i]->y[j] /= mod(aux[i]->y);
			aux[i]->h = h;
			aux[i]->col = c;
		}
	}
	aux[i] = 0;
	i = 0;
	if (len)
		while (sq[i])
			free(sq[i++]);
	free(sq);
	return (aux);
}

t_cylinder	**add_cy(t_cylinder **cy, double *O, double *v, double h, double d,
					int c)
{
	t_cylinder	**aux;
	double		Vn[3];
	int			len;
	int			i;
	int			j;

	len = 0;
	while (cy[len])
		len++;
	if (!(aux = (t_cylinder **)malloc(sizeof(t_cylinder *) * (len + 2))))
		return (cy);
	i = -1;
	while (++i < 3)
		Vn[i] = v[i] / mod(v);
	i = -1;
	while(++i < len + 1)
	{
		aux[i] = (t_cylinder *)malloc(sizeof(t_cylinder));
		j = -1;
		if (i < len)
		{
			while (++j < 3)
			{
				aux[i]->O[j] = cy[i]->O[j];
				aux[i]->v[j] = cy[i]->v[j];
			}
			aux[i]->col = cy[i]->col;
			aux[i]->d = cy[i]->d;
			aux[i]->h = cy[i]->h;
		}
		else
		{
			while (++j < 3)
			{
				aux[i]->O[j] = O[j];
				aux[i]->v[j] = Vn[j];
			}
			aux[i]->col = c;
			aux[i]->d = d;
			aux[i]->h = h;
		}
	}
	aux[i] = 0;
	i = 0;
	if (len)
		while (cy[i])
			free(cy[i++]);
	free(cy);
	return (aux);
}

t_box	**add_bx(t_box **bx, double *O, double *v, double h, int c)
{
	t_box		**aux;
	double		Vn[3];
	int			len;
	int			i;
	int			j;

	len = 0;
	while (bx[len])
		len++;
	if (!(aux = (t_box **)malloc(sizeof(t_box *) * (len + 2))))
		return (bx);
	i = -1;
	while (++i < 3)
		Vn[i] = v[i] / mod(v);
	i = -1;
	while(++i < len + 1)
	{
		aux[i] = (t_box *)malloc(sizeof(t_box));
		j = -1;
		if (i < len)
		{
			while (++j < 3)
			{
				aux[i]->O[j] = bx[i]->O[j];
				aux[i]->v[j] = bx[i]->v[j];
				aux[i]->x[j] = bx[i]->x[j];
				aux[i]->y[j] = bx[i]->y[j];
			}
			aux[i]->h = bx[i]->h;
			aux[i]->col = bx[i]->col;
		}
		else
		{
			while (++j < 3)
			{
				aux[i]->O[j] = O[j];
				aux[i]->v[j] = Vn[j];
			}
			aux[i]->x[0] = 0;
			aux[i]->x[1] = -Vn[2];
			aux[i]->x[2] = Vn[1];
			j = -1;
			while (++j < 3)
				aux[i]->y[j] = cross_prod(Vn, aux[i]->x, j);
			j = -1;
			while (++j < 3)
				aux[i]->y[j] /= mod(aux[i]->y);
			aux[i]->h = h;
			aux[i]->col = c;
		}
	}
	aux[i] = 0;
	i = 0;
	if (len)
		while (bx[i])
			free(bx[i++]);
	free(bx);
	return (aux);
}

t_triangle	**add_tr(t_triangle **tr, double *A, double *B, double *C, int c)
{
	t_triangle	**aux;
	int			len;
	int			i;
	int			j;

	len = 0;
	while (tr[len])
		len++;
	if (!(aux = (t_triangle **)malloc(sizeof(t_triangle *) * (len + 2))))
		return (tr);
	i = -1;
	while(++i < len + 1)
	{
		aux[i] = (t_triangle *)malloc(sizeof(t_triangle));
		j = -1;
		if (i < len)
		{
			while (++j < 3)
			{
				aux[i]->A[j] = tr[i]->A[j];
				aux[i]->B[j] = tr[i]->B[j];
				aux[i]->C[j] = tr[i]->C[j];
				aux[i]->ba[j] = tr[i]->ba[j];
				aux[i]->cb[j] = tr[i]->cb[j];
				aux[i]->ac[j] = tr[i]->ac[j];
				aux[i]->nor[j] = tr[i]->nor[j];
			}
			aux[i]->col = tr[i]->col;
		}
		else
		{
			while (++j < 3)
			{
				aux[i]->A[j] = A[j];
				aux[i]->B[j] = B[j];
				aux[i]->C[j] = C[j];
				aux[i]->ba[j] = A[j] - B[j];
				aux[i]->cb[j] = B[j] - C[j];
				aux[i]->ac[j] = C[j] - A[j];
			}
			j = -1;
			while (j < 3)
				aux[i]->nor[j] = cross_prod(aux[i]->ba, aux[i]->ac, j);
			aux[i]->col = c;
		}
	}
	aux[i] = 0;
	i = 0;
	if (len)
		while (tr[i])
			free(tr[i++]);
	free(tr);
	return (aux);
}
