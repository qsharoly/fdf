/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:29:02 by qsharoly          #+#    #+#             */
/*   Updated: 2019/11/21 19:36:48 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define	X 0
#define Y 1
#define Z 2
#define W 3

typedef float	t_vec4[4];
typedef	float	t_mat4[4][4];

t_vec4	get_row4(t_mat4 m, int index)
{
	return (new_vec4_from_array(m[index]));
}

float	dot4(t_vec4 a, t_vec4 b)
{
	return (a[X] * b[X] + a[Y] * b[Y] + a[Z] * b[Z] + a[W] * b[W]);
}

t_vec4	transform(t_mat4 m, t_vec4 v)
{
	t_vec4	res;

	res[X] = dot(m[0], v);
	res[Y] = dot(m[1], v);
	res[Z] = dot(m[2], v);
	res[W] = dot(m[3], v);
	return (res);
}

t_mat4	transpose(t_mat4 m)
{
	t_mat4	tr;
	int		i;
	int		j;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			tr[j][i] = m[i][j];
			i++;
		}
		j++;
	}
	return (tr);
}

t_mat4	compose(t_mat4 a, t_mat4 b)
{
	t_mat4	c;
	t_mat4	b_transposed;
	int		i;
	int		j;

	b_transposed = transpose(b);
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			c[j][i] = dot4(a[j], b_transposed[i]);
			i++;
		}
		j++;
	}
	return (c);
}

t_mat4	zero_mat4(void)
{
	t_mat4	m;
	int		i;
	int		j;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			m[j][i] = 0.0;
			i++;
		}
		j++;
	}

	return (m);
}

t_mat4	identity_mat4(void)
{
	t_mat4	m;
	int		i;

	m = zero_mat4();
	m[0][0] = 1.0;
	m[1][1] = 1.0;
	m[2][2] = 1.0;
	m[3][3] = 1.0;
}

t_mat4	translation_mat(float x, float y, float z)
{
	t_mat4	m;

	m = identity_mat4();
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
	return (m);
}

t_mat4	scaling_mat(float x_scale, float y_scale, float z_scale)
{
	t_mat	m;

	m= zero_mat4();
	m[0][0] = x_scale;
	m[1][1] = y_scale;
	m[2][2] = z_scale;
	m[3][3] = 0;
	return (m);
}

t_mat4	rot_mat4_x(float angle)
{
	t_mat4	m;

	m = identity_mat4();
	m[1][1] = cos(angle);
	m[1][2] = -sin(angle);
	m[2][1] = sin(angle);
	m[2][2] = cos(angle);
	return (m);
}

t_mat4	rot_mat4_y(float angle)
{
	t_mat4	m;

	m = identity_mat4();
	m[0][0] = cos(angle);
	m[0][2] = -sin(angle);
	m[2][0] = cos(angle);
	m[2][2] = sin(angle);
	return (m);
}

t_mat4	rot_mat4_z(float angle)
{
	t_mat4	m;

	m = identity_mat4();
	m[0][0] = cos(angle);
	m[0][1] = -sin(angle);
	m[1][0] = cos(angle);
	m[1][1] = sin(angle);
	return (m);
}

t_mat4	rot_mat4(t_vec3 angles)
{
	t_mat4	m;

	m = zero_mat4();
	m[0][0] = 
