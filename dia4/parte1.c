/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parte1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 00:44:15 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/05 01:05:45 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_file		*file;
	t_file		*file_dup;
	int			x;
	int			y;
	int			i;
	int			j;
	int			result;
	int			rolls;

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
	y = file->lines;;
	x = ft_strlen(file->array_content[0]) - 1;
	file_dup = ft_file_dup(file);
	i = 0;
	result = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			rolls = 0;
			if (file->array_content[i][j] == '@')
			{
				if (j != 0 && file->array_content[i][j - 1] == '@')
					rolls++;
				if (j != x - 1 && file->array_content[i][j + 1] == '@')
					rolls++;
				if (i != 0 && file->array_content[i - 1][j] == '@')
					rolls++;
				if (i != y - 1 && file->array_content[i + 1][j] == '@')
					rolls++;
				if (i != 0 && j != 0 && file->array_content[i - 1][j - 1] == '@')
					rolls++;
				if (i != 0 && j != x - 1 && file->array_content[i - 1][j + 1] == '@')
					rolls++;
				if (i != y - 1 && j != 0 && file->array_content[i + 1][j - 1] == '@')
					rolls++;
				if (i != y - 1 && j != x - 1 && file->array_content[i + 1][j + 1] == '@')
					rolls++;
				if (rolls < 4)
				{
					result++;
					file_dup->array_content[i][j] = 'x';
				}
			}
			j++;
		}
		i++;
	}
	ft_file_print(file_dup);
	printf("\nResult: %d\n", result);
	ft_file_clear(&file);
	ft_file_clear(&file_dup);
	return (0);
}
