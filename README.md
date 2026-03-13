
*This project has been created as part of the 42 curriculum by oharoon(Omeir Haroon), pedrovmota*

# Minishell

## Description
`minishell` is a small Bash-like shell written in C.

The goal of this project is to understand and implement core Unix shell behavior with a strong focus on:
- Process creation and synchronization (`fork`, `execve`, `wait*`)
- File descriptor management (`dup`, `dup2`, `pipe`, redirections)
- Command parsing and execution flow
- Environment handling and shell builtins
- Signal behavior in interactive mode

The mandatory part implements the subset required by the subject:
- Interactive prompt with history
- Execution of commands from `PATH`, absolute paths, and relative paths
- Quotes handling (`'` and `"`)
- Redirections (`<`, `>`, `<<`, `>>`)
- Pipes (`|`)
- Environment expansion (`$VAR`) and last exit status (`$?`)
- Builtins:
  - `echo` (`-n`)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Interactive signals:
  - `Ctrl-C`: new prompt on a new line
  - `Ctrl-D`: exit shell
  - `Ctrl-\`: ignored

The project follows the 42 Minishell constraints:
- Written in C
- Built with `cc` and flags `-Wall -Wextra -Werror`
- Norm-compliant
- No memory leaks in project code

## Instructions

### 1. Prerequisites
On Linux, install development packages for `readline` and `ncurses` if they are missing.

### 2. Build
From the repository root:

```bash
make
```

Useful Makefile targets:
- `make` or `make all`: build `minishell`
- `make clean`: remove object files
- `make fclean`: remove object files and binary
- `make re`: rebuild from scratch

### 3. Run

```bash
./minishell
```

Optional helper targets available in this repository:

```bash
make n     # build and run minishell
make e     # run minishell with empty environment (env -i)
make d     # run with valgrind and project suppressions
make f     # run with full valgrind leak checks
```

### 4. Basic usage examples

```bash
minishell$ ls -la
minishell$ echo "hello $USER"
minishell$ cat < input.txt | grep minishell > output.txt
minishell$ echo $?
```

## Technical Notes
- The shell uses one global variable only for signal number reporting, as required by the subject.
- Behavior for required features is aligned with Bash reference behavior.
- Unrequired features (for mandatory), such as `;` and `\` handling outside required scope, are intentionally not implemented.
- Memory reported as leaking from the `readline` library itself is expected and accepted by the subject; only leaks from project code are considered faults.

## Bonus Part
The subject bonus includes:
- `&&` and `||` with parentheses for priority
- Wildcard `*` expansion in the current working directory

Bonus evaluation is valid only if all mandatory requirements are fully correct.

## Resources

### Project references
- 42 Minishell subject PDF (official project requirements)
- GNU Bash Reference Manual: https://www.gnu.org/software/bash/manual/
- POSIX Shell Command Language: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
- Linux man pages: https://man7.org/linux/man-pages/
  - `man 2 fork`, `man 2 execve`, `man 2 waitpid`, `man 2 pipe`, `man 2 dup2`, `man 7 signal`

