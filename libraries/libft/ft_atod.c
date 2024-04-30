/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:41:43 by ubazzane          #+#    #+#             */
/*   Updated: 2024/04/30 12:15:01 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double process_integer_part(const char **str, double *res, int sign)
{
	while (**str >= '0' && **str <= '9')
	{
		if (*res > DBL_MAX / 10.0)
		{
			if (sign == 1)
				return DBL_MAX;
			else
				return DBL_MIN;
		}
		*res = *res * 10.0 + (*(*str)++ - '0');
	}
	return *res;
}

double process_fractional_part(const char **str, double *res, double *place)
{
	if (*(*str) == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			if (*place < DBL_MIN * 10.0)
				break;
			*res += (*(*str)++ - '0') * (*place);
			*place /= 10;
		}
	}
	return *res;
}

double ft_atod(const char *str)
{
	double res = 0.0;
	int sign = 1;
	double place = 0.1;

	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = process_integer_part(&str, &res, sign);
	if (res == DBL_MAX || res == DBL_MIN)
		return res;
	res = process_fractional_part(&str, &res, &place);
	return (sign * res);
}
