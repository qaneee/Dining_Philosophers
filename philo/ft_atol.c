/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:52:00 by arvardan          #+#    #+#             */
/*   Updated: 2025/11/01 12:29:31 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atol(const char *str)
{
	long	n;
	int		sign;

	if (!str || !*str)
		return (0);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	sign = set_sign(&str);
	if (!ft_isdigit(*str))
		return (0);
	n = 0;
	while (ft_isdigit(*str))
	{
		n = n * 10 + (*str - '0');
		if ((sign == 1 && n > INT_MAX) || (sign == -1 && n > (long)INT_MAX + 1))
			return (0);
		str++;
	}
	if (*str != '\0')
		return (0);
	return (n * sign);
}
