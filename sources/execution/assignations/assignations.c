#include "minislay.h"

//Retrouve la clef et passe a la suivante
static bool	find_key_in_env(t_shel **minishell, char *key, char *value)
{
	if (*minishell)
	{
		if ((*minishell)->expt)
		{
			// Chercher la clef dans l'arbre.
			// Copier l'implementation du main de avlt			
		
			// Si la clef n'est pas dans l'arbre, l'ajouter dans la liste 
			// locale

		}
	}
}

//Trier la liste && implementer uen queue
static void	find_matching_key(t_shel **minishell, char *key, char *value)
{
	if (minishell)
	{
		if (key && value)
		{
			if (!find_key_in_env())
				find_key_in_local();

		}
		printf("Invalid key or value.\n");
	}
	printf("Invalid minishell.\n");
}

//SI assignation && commande -> assignation juste pour la commande
//sINON, ASSIGNATION permanente.
//Envoyer une liste d'assignations
bool	handle_assignations(t_shel **minishell, t_tokn *current)
{
	char	*key;
	char	*value;
	char	*assignation;

	if (current)
	{
		assignation = strdup(current->value);
		if (assignation)
		{
			key = assignation;
			strtok_r(key, "=", &value);
			find_matching_key();
		}
	}
	return (false);
}
