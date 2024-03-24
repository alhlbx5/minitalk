/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhalab <aalhalab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:24:56 by aalhalab          #+#    #+#             */
/*   Updated: 2024/03/24 23:35:34 by aalhalab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int	ft_atoi(const char *str)
{
	int	g[2];

	g[0] = 0;
	g[1] = 0;
	while ((*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	(*str == '+' || *str == '-') && (g[1] = *(str++));
	while (*str >= '0' && *str <= '9')
		g[0] = (g[0] * 10) + (*(str++) - 48);
	return (g[0] * (((2 * (g[1] == '-')) - 1) * -1));
}

void	send_bit(int pid, int bit)
{
	if (bit == 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(100);
}

void	send_char(int pid, char c)
{
	int	j;
	int	bit;

	j = 7;
	while (j >= 0)
	{
		bit = (c >> j) & 1;
		send_bit(pid, bit);
		j--;
	}
}

void	send_string(int pid, char *str)
{
	int	len;
	int	i;
	int	bit;

	len = strlen(str);
	i = 31;
	while (i >= 0)
	{
		bit = (len >> i) & 1;
		send_bit(pid, bit);
		i--;
	}
	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		write(1, "error\n", 6);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	send_string(pid, argv[2]);
	return (0);
}
