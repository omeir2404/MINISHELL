#include "../../include/minishell.h"

// int		str_in_str(char *str, char *find)
// {
// 	int	i;
// 	int	o;
// 	int	found;
// 	int	keep;

// 	i = 0;
// 	keep = 0;
// 	while (str[i])
// 	{
// 		o = 0;
// 		if (find[o] == str[i])
// 		{
// 			keep = i;
// 			while (find[o] == str[i])
// 			{
// 				o++;
// 				i++;
// 			}
// 			if (find[o] == '\0')
// 				return (i);
// 		    i = keep;
// 		}
// 		o = 0;
// 		i++;
// 	}
// 	return (0);
// }

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

// void remove_part_str(char *str, const char *remove) {
//     char *pos = str;
//     int len = strlen(remove);

//     while ((pos = strstr(pos, remove)) != NULL) {
//         memmove(pos, pos + len, strlen(pos + len) + 1);
//     }
// }
void remove_part_str(char *str, const char *remove)
{
    char *pos = strstr(str, remove);
    if (pos != NULL) {
        ft_memmove(pos, pos + strlen(remove), strlen(pos + strlen(remove)) + 1);
    }
}
// char	*remove_part_str(char *str, char *remove)
// {
// 	int	i;
// 	int	r_location;
// 	char	*ret;

// 	i = 0;
// 	ret = NULL;
// 	if (!str || !remove)
// 		return (NULL);
// 	r_location = str_in_str(str, remove);
// 	if (!r_location)
// 		return (NULL);
// 	ret = malloc(sizeof(char) * ft_strlen(str) - ft_strlen(remove) + 1);
// 	while (i < r_location)
// 	{
// 		ret[i] = str[i];
// 		i++;
// 	}
// 	while (i < ft_strlen(remove))
// 		i++;
// 	while (str[i])
// 	{
// 		ret[i] = str[i];
// 		i++;
// 	}
// 	return (ret);
// }

// void    redirect(char **matrix)
// {
// 	// int w;
// 	int l;
// 	char *last_one;
// 	// char **matrix;
// 	int fd;
	
// 	// matrix = ft_split(str, ' ');
// 	l = 0;
// 	last_one = NULL;
// 	// w = 0;
// 	while (matrix[l])
// 	{
// 		if (!ft_strncmp(matrix[l], ">", ft_strlen(matrix[l])))
// 		{
// 			if (!matrix[l + 1])
// 			{
// 				printf("minishell: syntax error near unexpected token `newline'\n");
// 				return ;
// 			}
// 			if (last_one)
// 				open(last_one, O_WRONLY | O_CREAT, 0644);
// 			last_one = matrix[l + 1];
// 		}
// 		l++;
// 	}
// 	if (last_one)
// 	{
// 		fd = open(last_one, O_WRONLY | O_CREAT, 0644);
// 		sh()->redirect.output = fd;
// 		dup2(fd, STDOUT_FILENO); //fix this!!!!!! it changes ouput of the entire minishell
// 	}
// }

// void    redirect_funct(void)
// {
// 	int	i;
// 	char	**matrix;
// 	char	*last_one;
// 	int	fd;

// 	i = 0;
// 	if (!sh()->input)
// 	{
// 		printf("\n");
// 		return ;
// 	}
// 	last_one = NULL;
// 	matrix = ft_split(sh()->input, ' ');
// 	while (matrix[i])
// 	{
// 		if (!ft_strncmp(matrix[i], ">", 1))
// 		{
// 			if (matrix[i + 1])
// 			{
// 				sh()->redirect.outfile = matrix[i + 1];// is the ouptut filename create if needed.  
// 				if (last_one)
// 					open(last_one, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 				last_one = matrix[i + 1];
// 			}
// 			else if (i < 1)
// 				printf("expected before: \'>\'\n");
// 			else if (!matrix[i + 1])
// 			{
// 				printf("output filepath expected");
// 				return ;
// 			}
// 		}
// 		i++;
// 	}
// 	if (last_one)
// 	{
// 		fd = open(last_one, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		sh()->redirect.output = fd;
// 		dup2(fd, STDOUT_FILENO); //fix this!!!!!! it changes ouput of the entire minishell
// 		remove_part_str(sh()->input, " >");
// 		remove_part_str(sh()->input, sh()->redirect.outfile);
// 	}
// 	else
// 		return ;
// 	// dup2(open(matrix[1], O_RDWR), 1);
// 	// sh()->input = str;
	
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