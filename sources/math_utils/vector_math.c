/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:51:20 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:51:22 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float				dot_product(cl_float3 vec1, cl_float3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

float				vec_magnitude(cl_float3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

cl_float3			vec_normalize(cl_float3 vec)
{
	const float	vec_length = vec_magnitude(vec);

	return ((cl_float3){
		{vec.x / vec_length,
		vec.y / vec_length,
		vec.z / vec_length}});
}
