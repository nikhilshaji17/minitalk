/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkunnath <nkunnath@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:34:26 by nkunnath          #+#    #+#             */
/*   Updated: 2024/07/24 11:34:28 by nkunnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putstr(char *s, int *num_printed)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (s == NULL)
	{
		if (write(1, "(null)", 6) == -1)
			*num_printed = -1;
		else
			*num_printed += 6;
		return ;
	}
	while (s[i] != '\0')
	{
		x = write(1, &s[i], 1);
		if (x == -1)
		{
			*num_printed = -1;
			return ;
		}
		i += 1;
	}
	*num_printed += i;
}
