/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parte1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:08:22 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/07 12:44:49 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_file		*file;
	int			i, j;
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
	i = 0;
	result = 0;
	while (i < file->lines)
	{
		j = 0;
		while (j < file->list_content->len - 1)
		{
			if (file->array_content[i][j] == 'S')
				file->array_content[i + 1][j] = '|';
			else if (file->array_content[i][j] == '^' && file->array_content[i - 1][j] == '|')
			{
				file->array_content[i][j + 1] = '|';
				file->array_content[i][j - 1] = '|';
				result++;
			}
			if (i != 0 && file->array_content[i - 1][j] == '|' && file->array_content[i][j] == '.')
			{
				file->array_content[i][j] = '|';
			}
			j++;
		}
		i++;
	}
	ft_file_print(file);
	printf("\nResult: %d\n", result);
	ft_file_clear(&file);
	return (0);
}