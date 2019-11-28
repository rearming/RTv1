/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:51:01 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:51:02 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

int			in_range_inclusive(float number, float min, float max)
{
	if (number >= min && number <= max)
		return (TRUE);
	else
		return (FALSE);
}
