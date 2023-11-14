#include "shell.h"

/**
 * execute_command - Execute a command with arguments in a child process.
 * @command_with_args: The command with its arguments.
 *
 * This function forks a child process to execute the given command along with
 * its arguments using the execve system call. It handles errors related to
 * forking, executing the command, and accessing the command's executable file.
 */
int main(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t read_size;
	int result;

	while (1)
	{
		prompt(); /* display the shell prompt */

		read_size = getline(&input, &input_size, stdin); /* read user input */
		if (read_size == -1)
		{
			free(input);
			return (0); /* exit loop and program on input failure */
		}

		if (input[read_size - 1] == '\n')
			input[read_size - 1] = '\0'; /* remove trailing newline */

		/* check if the user wants to exit the shell */
		if (_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			input = NULL;
			input_size = 0;
			exit(EXIT_SUCCESS); /* exit the shell gracefully */
		}
		/* Execute the command and handle errors */
		if (read_size > 1)
		{
			result = execute_command(_strtrim(input));
			if (result == -1)
				break;
		}
	}
	free(input);
	return (0);
}
