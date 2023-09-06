#ifndef CLASS_H
# define CLASS_H

# include <signal.h>

typedef enum token_status
{
	ENV_MODE_TOKEN,
	ENV_MODE_QUOTE,
	ENV_MODE_DQUOTE,
}						t_mode;

typedef struct s_env
{
	char				*var;
	char				*value;
	int					var_len;
	struct s_env		*next;
	int					unset;
}						t_env;

typedef struct s_redirection
{
	char				*infile;
	char				*outfile;
	int					input;
	int					output;
}						t_redirection;

typedef struct s_comands
{
	t_redirection		*redirect;
	char				**args;
	struct s_comands	*next;
}						t_commands;

typedef struct s_shell
{
	int					exit;
	char				*input;
	char				*current_path;
	char				**paths;
	t_env				*env;
	t_commands			*command;
	int					n_forks;
	int					pipes[2];
	char				**en;
	t_redirection		redirect;

	struct sigaction	control_c;
	struct sigaction	control_back_slash;
	struct sigaction	up_arrow;
	struct sigaction	down_arrow;
}						t_shell;

# define VERSION "1.4.2"
# define ERR_MALLOC "Error: malloc failed\n"
# define ERR_FORK "Error: fork failed\n"
# define ERR_PIPE "Error: pipe failed\n"
# define ERR_DUP2 "Error: dup2 failed\n"
# define ERR_OPEN "Error: open failed\n"
# define ERR_CLOSE "Error: close failed\n"
# define ERR_EXECVE "Error: execve failed\n"
# define SYNTAX_ERROR "Error: syntax error\n"
# define ERR_CD "Error: cd failed\n"
# define ERR_CHDIR "Error: chdir failed\n"
# define ERR_GETCWD "Error: getcwd failed\n"
# define ERR_ENV "Error: env failed\n"
# define ERR_EXIT "Error: exit failed\n"
# define ERR_UNSET "Error: unset failed\n"
# define ERR_EXPORT "Error: export failed\n"
# define ERR_EXPORT_INVALID_IDENTIFIER "not a valid identifier\n"
# define ERR_EXPORT_TOO_MANY_ARGUMENTS "too many arguments\n"

# define ERR(fd, msg) write(fd, msg, ft_strlen(msg))

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_GENERAL_ERROR 2
# define EXIT_COMMAND_NOT_EXECUTABLE 126
# define EXIT_COMMAND_NOT_FOUND 127
# define EXIT_INVALID_ARGUMENT 128
# define EXIT_INTERRUPTED_BY_CTRL_C 130
# define EXIT_STATUS_OUT_OF_RANGE 255

# define TOKEN_DQUOTE '\2'
# define TOKEN_QUOTE '\3'
# define TOKEN_PIPE '\4'
# define TOKEN_SPACE '\5'
# define TOKEN_SEMI_COLOM '\6'

#endif