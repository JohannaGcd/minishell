# include "executer.h"

void	execute_single_command(t_command *command, char **envp)
{
	if (command->in) //TODO: find a way to only call if a heredoc. use a flag.
		handle_heredoc(&command);
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) 
	{
        // Child process
		io_redirect(command);
		if (execve(command->command_args[0], command->command_args, envp) == -1)
        {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
    } 
	else 
	{
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

// int	execute_multiple_cmd(t_command **command, char **envp, t_minishell *mshell)
// {
// 	// Iterate over each command
// 	// Create a pipe for each, except last one
// 	// Each cmd 
// 		//gets input from previous pipe's read end 
// 		// and output to current pipe's write end (if not the last cmd)
// 	// for each cmd, 
// 		// fork child
// 		// dup2 
// 			//-> 1rst cmd only redirect output to pipe
// 			// middle -> redirect input from previous pipe and output to current pipe
// 			// last cmd: only redirect input from previous pipe
// 		// call execve()
// 	int pipe_fd[nbr_cmds-1][2];
// 	pid_t id_array[2];
// 	char *command_wp;

// 	while ((*command)->next)
// 	{
// 		if (pipe(pi))
// 	}
// }

// // In the parent
// // use waitpid in a loop to wait for each child


// TO DELETE: THIS FUNCTION WORKS FOR TWO COMMANDS ONLY.
int	execute_multiple_cmd(t_command **command, char **envp, t_minishell *mshell)
{
	// fork
	// pipe
	// redirect -> output of first command goes to second one
	int pipe_fd[2];
	pid_t id_array[2];
	char *command_wp;
	if (pipe(pipe_fd) == -1)
	{
		perror("Error with pipe in execute_multiple_cmd");
		return -1;
	}
	// Fork first child
	id_array[0] = fork();
	if (id_array[0] == -1)
		return (perror("error forking first child process"), EXIT_FAILURE);
	
	// Child process 1
	if (id_array[0] == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO); // Redirect STDOUT to pipe write-end
		close(pipe_fd[0]); //close unused read end
		close(pipe_fd[1]); // close write end after dup2;
		io_redirect(*command); // apply normal redirections if any
		command_wp = return_command_with_path((*command)->command_args[0], mshell);
		//printf("\n1here: %s\n", command_wp);
		if (execve(command_wp, (*command)->command_args, envp) == -1)
        {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
	}
	// Fork second child
	id_array[1] = fork();
	if (id_array[1] == -1)
		return (perror("error forking second child process"), EXIT_FAILURE);
	// Child process 2
	if (id_array[1] == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		io_redirect((*command)->next);
		command_wp = return_command_with_path((*command)->next->command_args[0], mshell);
		//printf("\n2here: %s\n", command_wp);
		if (execve(command_wp, (*command)->next->command_args, envp) == -1)
        {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
	}
	else
	{
		// what happens in Parent vs child?
		int status1;
		int status2;
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(id_array[0], &status1, 0);
		waitpid(id_array[1], &status2, 0);
	}
	return (0);
}