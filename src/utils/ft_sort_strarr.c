#include "minishell.h"

void ft_sort_strarr(char **arr)
{
    int i;
    int j;
    char *tmp;

    if (!arr)
        return;
    
    i = 0;
    while (arr[i])
    {
        j = i + 1;
        while (arr[j])
        {
            if (ft_strcmp(arr[i], arr[j]) > 0)
            {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
            j++;
        }
        i++;
    }
}