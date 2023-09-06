#include <minishell.h>

void	show_split(char **element)
{
	int	i;

	i = 0;
	if (!element)
	{
		printf("Double Pointer is Currently empty\n");
		return ;
	}
	while (element[i])
	{
		if (i == 0)
			printf("{");
		if (element[i + 1])
			printf("%s, ", element[i]);
		else if (element[i + 1] == NULL)
			printf("%s", element[i]);
		i++;
	}
	printf("}\n");
	printf("Len: %s%d%s\n", RED, i, RESET);
}

void	print_special(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == TOKEN_PIPE)
			printf("\\4");
		else if (s[i] == TOKEN_QUOTE)
			printf("\\3");
		else if (s[i] == TOKEN_DQUOTE)
			printf("\\2");
		else if (s[i] == TOKEN_SEMI_COLOM)
			printf("\\6");
		else if (s[i] == TOKEN_SPACE)
			printf(".");
		else
			printf("%c", s[i]);
		i++;
	}
	printf("\n");
}
