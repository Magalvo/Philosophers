#include "../../include/philosophers.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

int	ft_atoi(const char *str)
{
	int		signal;
	long	result;

	signal = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signal = -1;
		str++;
	}
	while (ft_isdigit(*str) && *str)
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * signal);
}
