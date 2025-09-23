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
	long	num;
	int		sign;

	if (!str || !*str)
		return (0);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	sign = set_sign(&str);
	if (!ft_isdigit(*str))
		return (0);
	num = 0;
	while (ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && num > (long)INT_MAX + 1))
			return (0);
		str++;
	}
	if (*str != '\0')
		return (0);
	return (num * sign);
}
