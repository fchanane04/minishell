// #include "lexer/lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "lexer/lexer.h"
typedef struct s_data
{
    char    *str;
    int     value;
}t_data;



enum token_types{
    WORD,
    OPERATION,
    SEMI,
};

int    ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return(i);
}

void    ft_putstr_fd(char *str, int fd)
{
    int i;

    i = 0;
    while(str[i] != '\0')
        write(fd, &str[i++], 1);
}

void    print_envp(char **envp, t_data *data)
{
    int i;
    int fd;

    i = 0;
    if (data[1].value == 1)
        fd = open(data[2].str, O_RDWR | O_CREAT, 0777);
    else
        fd = 1;
    while (envp[i] != NULL)
    {
        ft_putstr_fd(envp[i++], fd);
        write(fd, "\n", 1);
    }
}

char    *get_env(char *str, char **envp)
{
    int i;
    char *s;

    i = 0;
    while(envp[i] != NULL)
    {
        if (strncmp(envp[i], str, ft_strlen(str)) == 0)
        {
            s = strdup(envp[i] + ft_strlen(str) + 1);
            return(s);
        }
        i++;
    }
}

void    ft_echo(char **envp, t_data *data)
{
    int     i;
    int     fd;
    char    *s;

    i = 4;
    if (data[1].value == 1)
        fd = open(data[2].str, O_RDWR | O_CREAT, 0777);
    else
        fd = 1;
    while (data[i].str != NULL)
    {
        if (strcmp(data[i].str, "$") == 0)
        {
            s = get_env(data[++i].str, envp);
            ft_putstr_fd(s, fd);
            free(s);
        }
        else
            ft_putstr_fd(data[i].str, fd);
        write(fd, " ", 1);
        i++;
    }
    if (data[3].value)
        write(fd, "\n", 1);
}

void	ft_pwd(t_data *data)
{
    char buff[100];
    int fd;

    getcwd(buff, sizeof(buff));
    if (data[1].value == 1)
        fd = open(data[2].str, O_RDWR | O_CREAT, 0777);
    else
        fd = 1;
    write(fd, buff, strlen(buff));
    write(fd, "\n", 1);
}

void	ft_cd(t_data *data, char **envp)
{
    if (data[4].value == 1)
        chdir(data[4].str);
    else
        chdir(get_env("HOME", envp));
}

int     ft_size(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        i++;
    return(i);
}


char	**ft_unset(t_data *data, char **envp)
{
    char    **new_envp;
    int     i;
    int     j;

    i = 0;
    j = 0;
    if (data[4].value == 1)
    {
        new_envp = malloc(sizeof(char *) * ft_size(envp));
        while (i < ft_size(envp))
        {
            if (strncmp(data[4].str, envp[i], ft_strlen(data[5].str)) == 0)
                i++;
            else
                new_envp[j] = strdup(envp[i]);
            i++;
            j++;            
        }
        return(new_envp);
    }
    return(envp);
}

int	count_var(t_data *data)
{
    int i;

    i = 4;
    while (data[i].value == 1)
        i++;
    return (i - 4);
}

char	**ft_export(t_data *data, char **envp)
{
    char    **new_env;
    int     i;
    int     j;

    i = 0;
    j = 4;
    if (data[4].value == 1)
    {
        new_env = malloc(sizeof(char *) * ft_size(envp) + count_var(data) + 1);
        while (i < ft_size(envp))
        {
            new_env[i] = strdup(envp[i]);
            i++;
        }
        while (j - 4 < count_var(data))
            new_env[i++] = strdup(data[j++].str);
        
        new_env[i] = NULL;
        return(new_env);
    }
    return(envp);
}

// int main(int ac, char **av, char **envp)
// {
//     char *line;
//     int     i;
//     t_data *data;

//     i = 0;
//     data = malloc(sizeof(t_data) * 11);

//     data[0].str = "echo"; 
//     data[1].str = ">";
//     data[2].str = "cool";
//     data[3].str = "-n";
//     data[4].str = "HI=lool";
//     data[5].str = "VAR=hey";
//     data[6].str = "ARG=test";
//     data[7].str = "$";
//     data[8].str = "HOME";
//     data[9].str = "girl";
//     data[10].str = NULL;

//     while (i < 11)
//         data[i++].value = 0;
//     data[1].value = 0;
//     data[4].value = 1;
//     data[5].value = 1;
//     data[6].value = 1;
//     while ((line = readline("minishell@minihell>")) != NULL)
//     {
//         if (strncmp(line, "env", ft_strlen("env")) == 0)
//             print_envp(envp, data);
//         else if (strncmp(line, "pwd", ft_strlen("pwd")) == 0)
//             ft_pwd(data);
//         else if (strncmp(line, "echo", ft_strlen("echo")) == 0)
//             ft_echo(envp, data);
//         else if (strncmp(line, "exit", ft_strlen("exit")) == 0)
//             break;
//         else if (strncmp(line, "cd", ft_strlen("cd")) == 0)
//             ft_cd(data, envp);
//         else if (strncmp(line, "export", ft_strlen("export")) == 0)
//             envp = ft_export(data, envp);
//         else if (strncmp(line, "unset", ft_strlen("unset")) == 0)
//             envp = ft_unset(data, envp);
//         free(line);
//     }   
// }