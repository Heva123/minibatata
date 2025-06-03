// // // #include "../../minishell.h"

// // // int	is_operator(const char *s)
// // // {
// // // 	if (!s)
// // // 		return (0);
// // // 	if (*s == '|' || *s == '<' || *s == '>')
// // // 	{
// // // 		if ((s[0] == s[1]) && (s[0] == '<' || s[0] == '>'))
// // // 			return (2); // for << or >>
// // // 		return (1); // for | < >
// // // 	}
// // // 	return (0);
// // // }

// // // int	is_quote(char c)
// // // {
// // // 	return (c == '\'' || c == '\"');
// // // }

// // // void	update_quote_state(char c, int *in_single, int *in_double)
// // // {
// // // 	if (c == '\'' && !(*in_double))
// // // 		*in_single = !(*in_single);
// // // 	else if (c == '\"' && !(*in_single))
// // // 		*in_double = !(*in_double);
// // // }

// // // char	*strip_quotes(const char *token)
// // // {
// // // 	int		in_single = 0, in_double = 0, i = 0, j = 0;
// // // 	char	*clean = malloc(strlen(token) + 1);
// // // 	if (!clean)
// // // 		return (NULL);
// // // 	while (token[i])
// // // 	{
// // // 		update_quote_state(token[i], &in_single, &in_double);
// // // 		if (!(token[i] == '\'' && !in_double) && !(token[i] == '\"' && !in_single))
// // // 			clean[j++] = token[i];
// // // 		i++;
// // // 	}
// // // 	clean[j] = '\0';
// // // 	return (clean);
// // // }

// // // char	**tokenize_input(const char *input)
// // // {
// // // 	char	**tokens = malloc(sizeof(char *) * 1024); // adjust size as needed
// // // 	int		i = 0, start = 0, in_single = 0, in_double = 0, t = 0;

// // // 	while (input[i])
// // // 	{
// // // 		update_quote_state(input[i], &in_single, &in_double);
// // // 		if (!in_single && !in_double && (input[i] == ' ' || is_operator(&input[i])))
// // // 		{
// // // 			if (i > start)
// // // 				tokens[t++] = strip_quotes(strndup(&input[start], i - start));
// // // 			if (is_operator(&input[i]))
// // // 			{
// // // 				int op_len = is_operator(&input[i]);
// // // 				tokens[t++] = strndup(&input[i], op_len);
// // // 				i += op_len;
// // // 			}
// // // 			else
// // // 				i++;
// // // 			while (input[i] == ' ')
// // // 				i++;
// // // 			start = i;
// // // 		}
// // // 		else
// // // 			i++;
// // // 	}
// // // 	if (i > start)
// // // 		tokens[t++] = strip_quotes(strndup(&input[start], i - start));
// // // 	tokens[t] = NULL;
// // // 	return (tokens);
// // // }

// // #include "../../minishell.h"

// // int is_operator(const char *s)
// // {
// //     if (!s)
// //         return (0);
// //     if (*s == '|' || *s == '<' || *s == '>')
// //     {
// //         if ((*s == '>' && *(s + 1) == '>') || (*s == '<' && *(s + 1) == '<'))
// //             return (2);
// //         return (1);
// //     }
// //     return (0);
// // }

// // int is_quote(char c)
// // {
// //     return (c == '\'' || c == '\"');
// // }

// // void update_quote_state(char c, int *in_single, int *in_double)
// // {
// //     if (c == '\'' && !(*in_double))
// //         *in_single = !(*in_single);
// //     else if (c == '\"' && !(*in_single))
// //         *in_double = !(*in_double);
// // }

// // char *strip_quotes(const char *token)
// // {
// //     int in_single = 0, in_double = 0, i = 0, j = 0;
// //     char *clean = malloc(strlen(token) + 1);
    
// //     if (!clean)
// //         return (NULL);
// //     while (token[i])
// //     {
// //         update_quote_state(token[i], &in_single, &in_double);
// //         if (!(token[i] == '\'' && !in_double) && !(token[i] == '\"' && !in_single))
// //             clean[j++] = token[i];
// //         i++;
// //     }
// //     clean[j] = '\0';
// //     return (clean);
// // }

// // char **tokenize_input(const char *input)
// // {
// //     char **tokens = malloc(sizeof(char *) * 1024);
// //     int i = 0, start = 0, in_single = 0, in_double = 0, t = 0;

// //     if (!tokens)
// //         return (NULL);
// //     while (input[i])
// //     {
// //         update_quote_state(input[i], &in_single, &in_double);
// //         if (!in_single && !in_double && (input[i] == ' ' || is_operator(&input[i])))
// //         {
// //             if (i > start)
// //                 tokens[t++] = strip_quotes(strndup(&input[start], i - start));
// //             if (is_operator(&input[i]))
// //             {
// //                 int op_len = is_operator(&input[i]);
// //                 tokens[t++] = strndup(&input[i], op_len);
// //                 i += op_len;
// //                 start = i;
// //                 continue;
// //             }
// //             while (input[i] == ' ')
// //                 i++;
// //             start = i;
// //         }
// //         else
// //             i++;
// //     }
// //     if (i > start)
// //         tokens[t++] = strip_quotes(strndup(&input[start], i - start));
// //     tokens[t] = NULL;
// //     return (tokens);
// // }


// #include "../../minishell.h"

// int is_operator(const char *s)
// {
//     if (!s)
//         return 0;
//     if (*s == '|' || *s == '<' || *s == '>')
//     {
//         if ((*s == '>' && *(s + 1) == '>') || (*s == '<' && *(s + 1) == '<'))
//             return 2;
//         return 1;
//     }
//     return 0;
// }

// void update_quote_state(char c, int *in_single, int *in_double)
// {
//     if (c == '\'' && !(*in_double))
//         *in_single = !(*in_single);
//     else if (c == '\"' && !(*in_single))
//         *in_double = !(*in_double);
// }

// char *strip_quotes(const char *token)
// {
//     int in_single = 0, in_double = 0;
//     int i = 0, j = 0;
//     char *clean = malloc(strlen(token) + 1);
    
//     if (!clean)
//         return NULL;
        
//     while (token[i])
//     {
//         update_quote_state(token[i], &in_single, &in_double);
//         if (!(token[i] == '\'' && !in_double) && !(token[i] == '\"' && !in_single))
//             clean[j++] = token[i];
//         i++;
//     }
//     clean[j] = '\0';
//     return clean;
// }

// char **tokenize_input(const char *input)
// {
//     char **tokens = malloc(sizeof(char *) * 1024);
//     int i = 0, start = 0, in_single = 0, in_double = 0, t = 0;

//     if (!tokens)
//         return NULL;

//     while (input[i])
//     {
//         update_quote_state(input[i], &in_single, &in_double);
        
//         if (!in_single && !in_double && 
//             (input[i] == ' ' || is_operator(&input[i])))
//         {
//             if (i > start)
//                 tokens[t++] = strip_quotes(strndup(&input[start], i - start));
            
//             if (is_operator(&input[i]))
//             {
//                 int op_len = is_operator(&input[i]);
//                 tokens[t++] = strndup(&input[i], op_len);
//                 i += op_len;
//                 start = i;
//                 continue;
//             }
            
//             while (input[i] == ' ') 
//                 i++;
//             start = i;
//         }
//         else
//         {
//             i++;
//         }
//     }

//     if (i > start)
//         tokens[t++] = strip_quotes(strndup(&input[start], i - start));
    
//     tokens[t] = NULL;
//     return tokens;
// }

#include "../../minishell.h"

// Move quote-related functions to quotes.c
// Only keep tokenization logic here

int is_operator(const char *s)
{
    if (!s)
        return 0;
    if (*s == '|' || *s == '<' || *s == '>')
    {
        if ((*s == '>' && *(s + 1) == '>') || (*s == '<' && *(s + 1) == '<'))
            return 2;
        return 1;
    }
    return 0;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = dest;
    const unsigned char *s = src;
    
    while (n--)
        *d++ = *s++;
    return dest;
}

static char *ft_strndup(const char *s, size_t n)
{
    char *dup;
    size_t len = 0;

    while (len < n && s[len])
        len++;
    
    dup = malloc(len + 1);
    if (!dup)
        return NULL;
    
    ft_memcpy(dup, s, len);
    dup[len] = '\0';
    return dup;
}

char **tokenize_input(const char *input)
{
    char **tokens = malloc(sizeof(char *) * 1024);
    int i = 0, start = 0, t = 0;
    int quote_state[2] = {0}; // [0] for single, [1] for double

    if (!tokens)
        return NULL;

    while (input[i])
    {
        update_quote_state(input[i], &quote_state[0], &quote_state[1]);
        
        if (!quote_state[0] && !quote_state[1] && 
            (input[i] == ' ' || is_operator(&input[i])))
        {
            if (i > start)
            {
                char *token = ft_strndup(&input[start], i - start);
                tokens[t++] = process_quotes(token); // Moved to quotes.c
                free(token);
            }
            
            if (is_operator(&input[i]))
            {
                int op_len = is_operator(&input[i]);
                tokens[t++] = ft_strndup(&input[i], op_len);
                i += op_len;
                start = i;
                continue;
            }
            
            while (input[i] == ' ') 
                i++;
            start = i;
        }
        else
        {
            i++;
        }
    }

    if (i > start)
    {
        char *token = ft_strndup(&input[start], i - start);
        tokens[t++] = process_quotes(token); // Moved to quotes.c
        free(token);
    }
    
    tokens[t] = NULL;
    return tokens;
}