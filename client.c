/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkunnath <nkunnath@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:37:12 by nkunnath          #+#    #+#             */
/*   Updated: 2024/12/19 18:37:13 by nkunnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_pid = BUSY;

static void	end_handler(int signo)
{
	write(STDOUT_FILENO, "Ok!\n", 4);
	exit(EXIT_SUCCESS);
}

static void	ack_handler(int signo)
{
	g_pid = READY;
}

void	send_signal_to_process(pid_t pid, char letter)
{
	int	bit;

	bit = 0;
	while (bit < CHAR_BIT)
	{
		if (letter & (0x80 >> bit))
			Kill(pid, SIGUSR1);
		else
			Kill(pid, SIGUSR2);
		bit += 1;
		while (g_pid == BUSY)
			usleep(42);
		g_pid = BUSY;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_id;
	char	*message;
	int		i;

	if (argc != 3)
	{
		fputs("Usage = ./client <PID> <Message> \n", stderr);
		exit(EXIT_FAILURE);
	}
	server_id = atoi(argv[1]);
	message = argv[2];
	i = 0;
	Signal(SIGUSR1, ack_handler, false);
	Signal(SIGUSR2, end_handler, false);
	while (message[i] != '\0')
	{
		send_signal_to_process(server_id, message[i]);
		i += 1;
	}
	send_signal_to_process(server_id, '\0');
	return (EXIT_SUCCESS);
}
