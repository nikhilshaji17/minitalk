/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkunnath <nkunnath@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:34:17 by nkunnath          #+#    #+#             */
/*   Updated: 2024/07/24 11:34:19 by nkunnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static void	print_number(unsigned long long n, char *table, int *num_printed)
{
	char	result;
	int		x;

	if (n > 0)
	{
		result = table[n % 16];
		print_number((n / 16), table, num_printed);
		if (*num_printed == -1)
			return ;
		x = write(1, &result, 1);
		if (x == -1)
		{
			*num_printed = -1;
			return ;
		}
		*num_printed += 1;
	}
}

void	ft_puthex(unsigned long long n, char c, int *num_printed)
{
	char	table_lower[17];
	char	table_upper[17];
	int		x;

	ft_strcpy(table_lower, "0123456789abcdef");
	ft_strcpy(table_upper, "0123456789ABCDEF");
	if (n == 0)
	{
		x = write(1, "0", 1);
		if (x == -1)
		{
			*num_printed = -1;
			return ;
		}
		*num_printed += 1;
		return ;
	}
	if (c == 'x')
		print_number(n, table_lower, num_printed);
	else
		print_number(n, table_upper, num_printed);
}
