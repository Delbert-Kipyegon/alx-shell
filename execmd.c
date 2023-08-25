#include "main.h"

void execmd(char **argv)
{
    char *command = NULL, *actual_command = NULL;
    int status;

    if (argv)
    {
        /* Execute the command in a child process */
        pid_t pid = fork();
        if (pid == 0)
        {
            /* get the command */
            command = argv[0];

            /* generate the path to this command before passing it to execve */
            actual_command = get_location(command);

            /* check if the command exists */
            if (actual_command == NULL)
            {
                fprintf(stderr, "No such file or directory: %s\n", command);
                exit(1);
            }

            if (execve(actual_command, argv, NULL) == -1)
            {
                perror("Error executing command");
                exit(1);
            }
        }

        else if (pid < 0)
        {
            perror("Fork error");
        }
        else
        {
            /* Parent process */
            
            waitpid(pid, &status, 0); /* Wait for the child to finish */
        }
    }
}