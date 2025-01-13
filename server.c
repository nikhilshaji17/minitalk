/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkunnath <nkunnath@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:37:28 by nkunnath          #+#    #+#             */
/*   Updated: 2024/12/19 18:37:30 by nkunnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int signo, siginfo_t *info, void *more_info)
{
	static char		c;
	static int		bit;
	static pid_t	client_pid;

	(void)more_info;
	if (info->si_pid)
		client_pid = info->si_pid;
	if (signo == SIGUSR1)
		c = c | (0b10000000 >> bit);
	else if (signo == SIGUSR2)
		c = c & ~(0b10000000 >> bit);
	if (++bit == 8)
	{
		bit = 0;
		if (c == '\0')
		{
			write(STDOUT_FILENO, "\n", 1);
			kill_wrapper(client_pid, SIGUSR2);
			c = 0;
			return ;
		}
		write(STDOUT_FILENO, &c, 1);
		c = 0;
	}
	kill_wrapper(client_pid, SIGUSR1);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("PID: %d\n", pid);
	sigac_wrapper(SIGUSR1, handle_signal, true);
	sigac_wrapper(SIGUSR2, handle_signal, true);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
