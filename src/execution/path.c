#include "minishell.h"

char	**get_paths(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}



char *find_command_path(char *cmd, char **envp) {
    char **paths;
    char *full_path;
    char *temp;
    int i;

    // If cmd starts with /, ./, or ../, check directly without PATH
    if (ft_strchr(cmd, '/')) {
        if (access(cmd, X_OK) == 0)
            return ft_strdup(cmd);  // Return copy of absolute path
        return NULL;
    }

    paths = get_paths(envp);
    full_path = NULL;
    temp = NULL;
    i = 0;
    
    if (!paths) 
        return NULL;
        
    while (paths[i]) {
        temp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(temp, cmd);
        free(temp);
        if (access(full_path, X_OK) == 0) {
            ft_free(paths);
            return full_path;
        }
        free(full_path);
        i++;
    }
    ft_free(paths);
    return NULL;
}