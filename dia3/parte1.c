/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parte1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:14:03 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/03 23:43:43 by ide-dieg         ###   ########.fr       */
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
	char		batery[3];
	char		*max_digit;
	int			result;

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
		max_digit = search_max_digit(current_line->str, ft_strlen(current_line->str) - 2);
		batery[0] = *max_digit;
		batery[1] = *search_max_digit(max_digit + 1, ft_strlen(max_digit + 1) - 1);
		printf("Batery: %s  ->  ", batery);
		printf("%s", current_line->str);
		result += ft_atoi(batery);
		current_line = current_line->next;
	}
	printf("\nResult: %d\n", result);
	ft_file_clear(&file);
	return (0);
}