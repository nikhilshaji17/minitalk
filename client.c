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

static void	end_handler(void)
{
	write(STDOUT_FILENO, "Ok!\n", 4);
	exit(EXIT_SUCCESS);
}

static void	ack_handler(void)
{
	g_pid = READY;
}

void	send_signal_to_process(pid_t server_pid, char letter)
{
	int	bit;

	bit = 0;
	while (bit < CHAR_BIT)
	{
		if (letter & (0x80 >> bit))
			kill_wrapper(server_pid, SIGUSR1);
		else
			kill_wrapper(server_pid, SIGUSR2);
		bit += 1;
		while (g_pid == BUSY)
			usleep(42);
		g_pid = BUSY;
	}
}

static	int	valid_pid(char *str)
{
	int	length;
	int	i;

	i = 0;
	length = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t' || (str[i] >= 9 && str[i] <= 13))
			i += 1;
		if (str[i] == '+' || str[i] == '-')
			i += 1;
		while (ft_isdigit(str[i]))
		{
			length += 1;
			i += 1;
			if (length > 7)
				return (-1);
		}
		while (str[i] == ' ' || str[i] == '\t' || (str[i] >= 9 && str[i] <= 13))
			i += 1;
		if (str[i] != '\0')
			return (-1);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	pid_t	server_id;
	char	*message;
	int		i;

	if (argc != 3)
	{
		ft_printf("Usage = ./client <PID> <Message>\n");
		exit(EXIT_FAILURE);
	}
	if (valid_pid(argv[1]) == -1)
		exit(EXIT_FAILURE);
	server_id = ft_atoi(argv[1]);
	if (server_id > MAX_LIMIT || server_id < MIN_LIMIT)
		exit(EXIT_FAILURE);
	message = argv[2];
	i = 0;
	sigac_wrapper(SIGUSR1, ack_handler, false);
	sigac_wrapper(SIGUSR2, end_handler, false);
	while (message[i] != '\0')
	{
		send_signal_to_process(server_id, message[i]);
		i += 1;
	}
	send_signal_to_process(server_id, '\0');
	return (EXIT_SUCCESS);
}
