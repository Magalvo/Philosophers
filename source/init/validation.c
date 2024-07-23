#include "../../include/philosophers.h"

int	error_treatment(int	num)
{
	if (num == 1)
		return(write(2, "Invalid Number of Guests\n", 26), 1);
	else if (num == 2)
		return(write(2, "No Time to Die ;-)\n", 20), 1);
	else if (num == 3)
		return(write(2, "He's a slow eater...\n", 22), 1);
	else if (num == 4)
		return(write(2, "8 Hours of sleep, right??\n", 27), 1);
	else if (num == 5)
		return(write(2, "Ther's no Ctrl+Z for spaghetti LOL\n", 36), 1);
	return (0);
}

int	check_args(char *argv)
{
	int	i;

	i = 1;
	while (argv[i] != '\0')
	{
		if (argv[i] < '0' || argv[i] > '9')
			return(1);
		i++;
	}
	return (0);
}

int	check_data(char **argv)
{
	int i;

	i = 1;
	if (ft_atoi(argv[1]) <= 0 || check_args(argv[1]) == 1)
		return(error_treatment(1), 1);
	while (i < 5)
	{
		if (argv[i] && (ft_atoi(argv[i]) <= 0 || check_args(argv[i]) == 1))
			return(error_treatment(i), 1);
		i++;
	}
	return (0);
}

