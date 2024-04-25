/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:14:10 by ubazzane          #+#    #+#             */
/*   Updated: 2024/04/25 12:49:47 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	quit_parsing(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	check_file_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(str + len - 3, ".rt", 3) != 0)
		quit_parsing("Error: incorrect file type\n");
}

char	*is_obj(char *str)
{
	if(ft_strcmp(str, "A"))
		return("A");
	else if (ft_strcmp(str, "C"))
		return("C");
	else if (ft_strcmp(str, "L"))
		return("L");
	else if (ft_strcmp(str, "sp"))
		return("sp");
	else if (ft_strcmp(str, "pl"))
		return("pl");
	else if (ft_strcmp(str, "cy"))
		return("cy");
	else
	 return ("error");
}

int	count_obj(char*** scene, char	*str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (scene[++i])
	{
		if (is_obj(scene[i][0]) == str)
			count++;
	}
	return (count);
}
