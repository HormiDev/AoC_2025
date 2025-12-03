/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parte2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:47:32 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/04 00:01:20 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"
#include <stdio.h>

char *search_max_digit(char *str, size_t len)
{
	char	*max_digit_position;
	size_t	i;
	char	max_digit;

	max_digit = 0;
	i = 0;
	while (i < len)
	{
		if (max_digit < str[i])
		{
			max_digit = str[i];
			max_digit_position = &str[i];
		}
		i++;
	}
	return (max_digit_position);
}

int	main(int argc, char **argv)
{
	t_file		*file;
	t_strlist	*current_line;
	char		batery[13];
	char		*max_digit;
	long long	result;

	if (argc != 2)
	{
		ft_dprintf(2, "Usage: %s <input_file>\n", argv[0]);
		return (1);
	}
	file = ft_create_file_from_filename(argv[1]);
	if (!file)
	{
		ft_dprintf(2, "Error: Could not create file from %s\n", argv[1]);
		return (1);
	}
	current_line = file->list_content;
	batery[2] = '\0';
	result = 0;
	while (current_line)
	{
		max_digit = search_max_digit(current_line->str, ft_strlen(current_line->str) - 12);
		batery[0] = *max_digit;
		max_digit = search_max_digit(max_digit + 1, ft_strlen(max_digit + 1) - 11);
		batery[1] = *max_digit;
		max_digit = search_max_digit(max_digit + 1, ft_strlen(max_digit + 1) - 10);
		batery[2] = *max_digit;
		max_digit = search_max_digit(max_digit + 1, ft_strlen(max_digit + 1) - 9);
		batery[3] = *max_digit;
		max_digit = search_max_digit(max_digit + 1, ft_strlen(max_digit + 1) - 8);
		batery[4] = *max_digit;
		max_digit = search_max_digit(max_digit + 1, ft_strlen(max_digit + 1) - 7);
		batery[5] = *max_digit;
		max_digit = search_max_digit(max_digit + 1, ft_strlen(max_digit + 1) - 6);
		batery[6] = *max_digit;
		max_digit = search_max_digit(max_digit + 1, ft_strlen(max_digit + 1) - 5);
		batery[7] = *max_digit;
		max_digit = search_max_digit(max_digit + 1, ft_strlen(max_digit + 1) - 4);
		batery[8] = *max_digit;
		max_digit = search_max_digit(max_digit + 1, ft_strlen(max_digit + 1) - 3);
		batery[9] = *max_digit;
		max_digit = search_max_digit(max_digit + 1, ft_strlen(max_digit + 1) - 2);
		batery[10] = *max_digit;
		max_digit = search_max_digit(max_digit + 1, ft_strlen(max_digit + 1) - 1);
		batery[11] = *max_digit;
		printf("Batery: %s  ->  ", batery);
		printf("%s", current_line->str);
		result += atoll(batery);
		current_line = current_line->next;
	}
	printf("\nResult: %lld\n", result);
	ft_file_clear(&file);
	return (0);
}