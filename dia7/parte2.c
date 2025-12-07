/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parte2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:00:20 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/07 22:29:57 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"
#include <stdio.h>


int	main(int argc, char **argv)
{
	t_file		*file;
	long		**array;
	int			i, j;
	long		final_result;

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
	final_result = 0;
	array = calloc(sizeof(long *), file->lines + 1);
	array[i] = calloc(sizeof(long), file->list_content->len);
	while (i < file->lines)
	{
		array[i + 1] = calloc(sizeof(long), file->list_content->len);
		j = 0;
		while (j < file->list_content->len - 1)
		{
			if (file->array_content[i][j] == 'S')
			{
				file->array_content[i + 1][j] = '|';
				array[i + 1][j] = 1;
			}
			if (file->array_content[i][j] == '^' && file->array_content[i - 1][j] == '|')
			{
				file->array_content[i][j + 1] = '|';
				array[i][j + 1] += array[i - 1][j];
				file->array_content[i][j - 1] = '|';
				array[i][j - 1] += array[i - 1][j];
			}
			if (i != 0 && file->array_content[i - 1][j] == '|' && file->array_content[i][j] == '.')
			{
				file->array_content[i][j] = '|';
			}
			if (file->array_content[i][j] == '|')
			{
				array[i][j] += array[i - 1][j];
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < file->list_content->len)
	{
		final_result += array[file->lines - 1][i];
		i++;
	}
	ft_file_print(file);
	printf("\nResult: %ld  possible routes\n", final_result);

	i = 0;
	while (i < file->lines)
	{
		/*j = 0;
		while (j < file->list_content->len)
		{
			printf("%2ld", array[i][j]);
			j++;
		}
		printf("\n");*/
		free(array[i]);
		i++;
	}
	free(array);
	ft_file_clear(&file);
	return (0);
}


//demasiado lento
/*long check_routes(t_file *file, int x, int y)
{
	long	result = 0;

	while (y < file->lines)
	{
		if (file->array_content[y][x] == '^')
		{
			result += check_routes(file, x - 1, y + 1);
			result += check_routes(file, x + 1, y + 1);
			return (result);
		}
		y++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_file		*file;
	int			i;
	long		result;

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
	while (i < file->list_content->len - 1)
	{
		if (file->array_content[0][i] == 'S')
		{
			//result = check_routes(file, i, 1);
			result = check_routes(file, i, 1);
			break;
		}
		i++;
	}
	
	printf("Result: %ld\n", result);
	ft_file_clear(&file);
	return (0);
}*/