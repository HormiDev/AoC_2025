/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parte1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:10:46 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/01 17:29:27 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"

int	main(int argc, char **argv)
{
	t_file		*file;
	int			dial;
	int			zero_count;
	t_strlist	*current_line;

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
	dial = 50;
	zero_count = 0;
	current_line = file->list_content;
	while (current_line)
	{
		if (dial == 0)
			zero_count++;
		if (current_line->str[0] == 'L')
		{
			dial -= ft_atoi(current_line->str + 1);
			while (dial < 0)
				dial += 100;
		}
		else if (current_line->str[0] == 'R')
		{
			dial += ft_atoi(current_line->str + 1);
			while (dial >= 100)
				dial -= 100;
		}
		current_line = current_line->next;
	}
	ft_printf("Zero count: %d\n", zero_count);
	ft_file_clear(&file);
	return (0);
}