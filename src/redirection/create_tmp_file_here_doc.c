/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tmp_file_here_doc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:32:27 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/04 17:40:43 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	create_file(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT, 0644);
	if (fd == -1)
		return (FALSE);
	return (TRUE);
}

char	*create_name_here_doc(int *id)
{
	char	*name;
	char	*id_str;
	t_bool	file_is_create;

	name = NULL;
	file_is_create = FALSE;
	while (file_is_create == FALSE)
	{
		id_str = ft_itoa(*id);
		name = ft_strdup(HERE_DOC_FILENAME);
		name = cft_strcat_realloc(name, id_str);
		name = cft_strcat_realloc(name, ".txt");
		free(id_str);
		*id += 1;
		if (create_file(name))
			file_is_create = TRUE;
	}
	printf("name file :%s\n", name);
	return (name);
}
