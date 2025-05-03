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

int execute_child(t_minishell *mshell, t_command *curr_cmd, char **envp, int *pipe_fd, int prev_read_end)
{
	char *command_wp;

	close(pipe_fd[0]);
	dup2(prev_read_end, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	io_redirect(curr_cmd);
	command_wp = return_command_with_path(curr_cmd->command_args[0], mshell);
	//printf("\n1here: %s\n", command_wp);
	if (execve(command_wp, curr_cmd->command_args, envp) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	
	return(0);
}

int execute_last_cmd(t_minishell *mshell, t_command *curr_cmd, char **envp, int prev_read_end)
{
	pid_t child_id;
	char *command_wp;

	child_id = fork();
	if (child_id < 0)
	{
		perror("fork did not work in execute_last_cmd");
		exit(EXIT_FAILURE);
	}
	if (child_id == 0)
	{
		dup2(prev_read_end, STDIN_FILENO);
		close(prev_read_end);
		io_redirect(curr_cmd);
		command_wp = return_command_with_path(curr_cmd->command_args[0], mshell);
		//printf("\n1here: %s\n", command_wp);
		if (execve(command_wp, curr_cmd->command_args, envp) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	close(prev_read_end);
	return (child_id);
}

int	update_pipe_fd(int *pipe_fd, int prev_read_end)
{
	close(pipe_fd[1]);
	if (prev_read_end != 0)
		close(prev_read_end);
	prev_read_end = dup(pipe_fd[0]);
	close(pipe_fd[0]);
	return (prev_read_end);
}

void	wait_for_children(pid_t child_id, int nbr_children)
{
	int status;
	
	if (waitpid(child_id, &status, 0) < 0)
	{
		perror("waitpid error");
	}
	while (nbr_children > 0)
	{
		wait(NULL);
		nbr_children--;
	}
}

int execute_multiple_cmd(char **envp, t_minishell *mshell)
{
	// Iterate over each command
	// Create a pipe for each, except last one
	// Each cmd 
		//gets input from previous pipe's read end 
		// and output to current pipe's write end (if not the last cmd)
	// for each cmd, 
		// fork child
		// dup2 
			//-> 1rst cmd only redirect output to pipe
			// middle -> redirect input from previous pipe and output to current pipe
			// last cmd: only redirect input from previous pipe
		// call execve()
	t_command *curr_cmd;
	int pipe_fd[2];
	int nbr_children;
	pid_t child_id;
	int prev_read_end;

	curr_cmd = mshell->commands;
	prev_read_end = STDIN_FILENO;
	nbr_children = 0;
	while (curr_cmd->next != NULL)
	{
		nbr_children++;
		if (pipe(pipe_fd) == -1)
		{
			perror("Error with pipe in execute_multiple_cmd");
			return -1;
		}
		child_id = fork();
		if (child_id == - 1)
			return (perror("error forking first child process"), EXIT_FAILURE);
		if (child_id == 0)
			execute_child(mshell, curr_cmd, envp, pipe_fd, prev_read_end);
		prev_read_end = update_pipe_fd(pipe_fd, prev_read_end);
		curr_cmd = curr_cmd->next;
	}
	child_id = execute_last_cmd(mshell, curr_cmd, envp, prev_read_end);
	wait_for_children(child_id, nbr_children);
	return (0);
}

// // In the parent
// // use waitpid in a loop to wait for each child


// // TO DELETE: THIS FUNCTION WORKS FOR TWO COMMANDS ONLY.
// int	execute_multiple_cmd(t_command **command, char **envp, t_minishell *mshell)
// {
// 	// fork
// 	// pipe
// 	// redirect -> output of first command goes to second one
// 	int pipe_fd[2];
// 	pid_t id_array[2];
// 	char *command_wp;
// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("Error with pipe in execute_multiple_cmd");
// 		return -1;
// 	}
// 	// Fork first child
// 	id_array[0] = fork();
// 	if (id_array[0] == -1)
// 		return (perror("error forking first child process"), EXIT_FAILURE);
	
// 	// Child process 1
// 	if (id_array[0] == 0)
// 	{
// 		dup2(pipe_fd[1], STDOUT_FILENO); // Redirect STDOUT to pipe write-end
// 		close(pipe_fd[0]); //close unused read end
// 		close(pipe_fd[1]); // close write end after dup2;
// 		io_redirect(*command); // apply normal redirections if any
// 		command_wp = return_command_with_path((*command)->command_args[0], mshell);
// 		//printf("\n1here: %s\n", command_wp);
// 		if (execve(command_wp, (*command)->command_args, envp) == -1)
//         {
//             perror("execve failed");
//             exit(EXIT_FAILURE);
//         }
// 	}
// 	// Fork second child
// 	id_array[1] = fork();
// 	if (id_array[1] == -1)
// 		return (perror("error forking second child process"), EXIT_FAILURE);
// 	// Child process 2
// 	if (id_array[1] == 0)
// 	{
// 		dup2(pipe_fd[0], STDIN_FILENO);
// 		close(pipe_fd[1]);
// 		close(pipe_fd[0]);
// 		io_redirect((*command)->next);
// 		command_wp = return_command_with_path((*command)->next->command_args[0], mshell);
// 		//printf("\n2here: %s\n", command_wp);
// 		if (execve(command_wp, (*command)->next->command_args, envp) == -1)
//         {
//             perror("execve failed");
//             exit(EXIT_FAILURE);
//         }
// 	}
// 	else
// 	{
// 		// what happens in Parent vs child?
// 		int status1;
// 		int status2;
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 		waitpid(id_array[0], &status1, 0);
// 		waitpid(id_array[1], &status2, 0);
// 	}
// 	return (0);
// }