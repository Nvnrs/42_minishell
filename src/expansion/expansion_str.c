/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:35:40 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/24 16:36:35 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Demarre a la single quote et avance jusqu'a la quote fermante.
 * 
 * @param str La chaine complete de depart
 * @param i Indice qui est egal a la position de la single quote
 * @param output Chaine de sortie, c'est ici qu'on fait la copie
 * @param i_out Indice qui indique la position du caractere dans output
 */

static void	handle_single_quote(char *str, int *i, char *output, int *i_out)
{
	output[*i_out] = str[*i];
	*i += 1;
	*i_out += 1;
	while (str[*i] != SINGLE_QUOTE)
	{
		output[*i_out] = str[*i];
		*i += 1;
		*i_out += 1;
	}
}


/**
 * Demarre a une double quote, effectue une expansion si besoin et avance
 * jusqu'a la quote fermante
 * 
 * @param str Adresse de la DOUBLE QUOTE rencontre dans la chaine initiale
 * @param output Chaine de sortie, c'est ici qu'on fait la copie
 * @param i_out_main Indice qui indique la position du caractere dans output
 * @param lst_env Liste des variables d'environnement
 * @return Nombre d'incrementation effectue dans str
 */

static int	handle_double_quote(char *str, char *output, int *i_out_main, t_list **lst_env)
{
	int	i;
	int	i_out;

	i = 0;
	i_out = *i_out_main;
	output[i_out++] = str[i++];
	while (str[i] != DOUBLE_QUOTE)
	{
		if (is_start_of_env_var(str, i))
		{
			i++;
			i+= expansion_var(&str[i], output, &i_out, lst_env);
			continue;
		}	
		output[i_out++] = str[i++];
	}
	*i_out_main = i_out;
	return (i);
}


/**
 * Free str and return new str with expansion 
 */
char	*expansion_str(char *str, t_list **lst_env)
{
	int		i;
	int		i_out;
	char	*output;

	init_int_zero(&i, &i_out, NULL, NULL);
	output = malloc((len_expansion_str(str, lst_env) + 1) * sizeof(char));
	output[0] = '\0';
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE)
			handle_single_quote(str, &i, output, &i_out);
		else if (str[i] == DOUBLE_QUOTE)
			i+= handle_double_quote(&str[i], output, &i_out, lst_env);
		else if (is_start_of_env_var(str, i))
		{
			i++;
			i+= expansion_var(&str[i], output, &i_out, lst_env);
			continue;
		}
		output[i_out++] = str[i++];
	}
	output[i_out] = '\0';
	free(str);
	return (output);
}
