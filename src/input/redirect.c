#include "../../include/minishell.h"
int str_in_str(const char *str, const char *find) {
    int big_len;
    int sub_len;
    int i = 0;

	sub_len = strlen(find);
	big_len = strlen(str);
    while (i <= big_len - sub_len) {
        int j = 0;
        while (j < sub_len && str[i + j] == find[j]) {
            j++;
        }
        if (j == sub_len) {
            return (i);
        }
        i++;
    }

    return (0);
}

// void remove_part_str(char *str, const char *remove)
// {
//     char *pos = strstr(str, remove);
//     if (pos != NULL) {
//         ft_memmove(pos, pos + strlen(remove), strlen(pos + strlen(remove)) + 1);
//     }
// }

char	*get_filename(char *input, int start)
{
	int		i;
	int		l;
	char	*filename;

	l = 0;
	while (input[start] == '>')
		start++;
	while (input[start] == ' ' || input[start] == '\t')
		start++;
	i = start;
	while (input[i] != ' ' && input[i] != '\0')
		i++;
	filename = malloc(sizeof(char) * (i - start) + 1);
	while (start < i)
	{
		filename[l] = input[start];
		l++;
		start++; 
	}
	filename[l] = '\0';
	return (filename);
}

void	redirect_out(void)
{
	int		i;
	char	*filename;
	int		fd;
	int		flag;

	i = 0;
	filename = NULL;
	flag = 0;
	while (sh()->input[i])
	{
		if (sh()->input[i] == '>' && sh()->input[i - 1] == ' ')
		{
			if (filename)
			{
				fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				close(fd);
				if (sh()->input[i + 1] == '>')
					flag = 1;
				else
					flag = 0;
				if (flag == 1)
					remove_part_str(sh()->input, " >>");
				else
					remove_part_str(sh()->input, " >");
				remove_part_str(sh()->input, filename);
				i -= (ft_strlen(filename) + 2);
				fd = 0;
			}
			else if (sh()->input[i + 1] == '>')
				flag = 1;
			filename = get_filename(sh()->input, i + 1);
		}
		i++;
	}

	if (filename)
	{
		if (flag == 0)
		{
			remove_part_str(sh()->input, " >");
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (flag == 1)
		{
			remove_part_str(sh()->input, " >>");
			fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		remove_part_str(sh()->input, filename);
		sh()->redirect.outfile = filename;
		sh()->redirect.output = fd;
	}
}

void	redirect_in(void)
{
	int		i;
	char	*filename;
	int		fd;

	i = 0;
	filename = NULL;
	while (sh()->input[i])
	{
		if (sh()->input[i] == '<' && sh()->input[i - 1] == ' ')
		{
			if (filename)
			{
				fd = open(filename, O_WRONLY, 0644);
				if (!fd)
				{
					printf("minishell: %s: No such file or directory\n", filename);
					return ;
				}
				close(fd);
				remove_part_str(sh()->input, " <");
				remove_part_str(sh()->input, filename);
				i -= (ft_strlen(filename) + 2);
			}
			filename = get_filename(sh()->input, i + 1);
		}
		i++;
	}
	if (filename)
	{
		fd = open(filename, O_RDWR | O_APPEND, 0777);
		if (!fd)
		{
			printf("minishell: %s: No such file or directory\n", filename);
			return ;
		}
		remove_part_str(sh()->input, " <");
		remove_part_str(sh()->input, filename);
		sh()->redirect.infile = filename;
		sh()->redirect.input = fd;
	}
}

void    redirect_funct(void)
{
	redirect_out();
	redirect_in();
}