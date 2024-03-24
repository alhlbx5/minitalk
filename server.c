/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhalab <aalhalab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:25:25 by aalhalab          #+#    #+#             */
/*   Updated: 2024/03/24 21:59:06 by aalhalab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void signal_handler(int sig) 
{
	static int received = 0;
	static int bits_received = 0;
	static int len = 0;
	static int len_received = 0;

	if (len_received < 32) 
	{
		len = len << 1;
		if (sig == SIGUSR1) 
			len = len | 1;
		len_received++;
	} 
	else 
	{
		received = received << 1;
		if (sig == SIGUSR1) 
			received = received | 1;
		bits_received++;
		if (bits_received == 8) 
		{
			write(1, &received, 1); 
			received = 0;
			bits_received = 0;
			len--;
			if (len == 0) 
			{
				write(1, "\n", 1);
				len_received = 0;
			}
		}
	}
}

int main(void)
{
	pid_t p;

	p = getpid();
	printf("Server PID: %d\n", p);

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1) 
		pause();
	return 0;
}