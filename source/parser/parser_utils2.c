/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:07:13 by ubazzane          #+#    #+#             */
/*   Updated: 2024/05/14 17:11:08 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	free_and_quit(char *str, char ***content);

void	check_objs(char ***content)
{
	int	i;

	i = -1;
	while (content[++i])
	{
		if (!ft_strcmp(is_obj(content[i][0]), "error"))
			free_and_quit("Error: invalid object detected\n", content);
		else if (!ft_strcmp(is_obj(content[i][0]), "A") \
				&& count_obj(content, "A") > 1)
			free_and_quit("Error: multiple ambient light detected\n", content);
		else if (!ft_strcmp(is_obj(content[i][0]), "C") \
				&& count_obj(content, "C") > 1)
			free_and_quit("Error: multiple cameras detected\n", content);
		else if (!ft_strcmp(is_obj(content[i][0]), "L") \
				&& count_obj(content, "L") > 1)
			free_and_quit("Error: multiple lights detected\n", content);
	}
}

static void	free_and_quit(char *str, char ***content)
{
	free_triple_pointer(content);
	quit_parsing(str);
}
