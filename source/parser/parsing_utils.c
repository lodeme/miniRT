/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:14:10 by ubazzane          #+#    #+#             */
/*   Updated: 2024/04/23 17:18:38 by ubazzane         ###   ########.fr       */
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
	if(strcmp(str, "A"))
		return("A");
	else if (strcmp(str, "C"))
		return("C");
	else if (strcmp(str, "L"))
		return("L");
	else if (strcmp(str, "sp"))
		return("sp");
	else if (strcmp(str, "pl"))
		return("pl");
	else if (strcmp(str, "cy"))
		return("cy");
	else
	 return ("error");
}
