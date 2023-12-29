#include "../header/minishell.h"
// ref https://insanecoding.blogspot.com/2007/11/pathmax-simply-isnt.html

// int ft_pwd(int mode, char **str)
// {
// 	char *pwd;
// 	char *pwd_ret;
// 	size_t size;
	
// 	pwd_ret = NULL;
// 	pwd = NULL;
// 	size = 1;
// 	while (pwd_ret == NULL)
// 	{
// 		pwd = ft_calloc(sizeof(char), size);
// 		if (pwd == NULL)
// 			return (perror("MALLOC : "), 1);
// 		pwd_ret = getcwd(pwd, size);
// 		if (pwd_ret == NULL && errno == ERANGE)
// 		{
// 			size++;
// 			free(pwd);
// 		}
// 		if (pwd_ret == NULL && errno != ERANGE)
// 			return (perror("GETCWD : "), 1);
// 	}
// 	if (mode == PRINT)
// 	{
// 		printf("%s\n", pwd_ret);
// 		free(pwd);
// 	}
// 	if (mode == GET)
// 		*str = pwd;	
// 	return (0);	
// }

int ft_pwd(int mode, char **str)
{
	char *pwd;
	char *pwd_ret;
	
	pwd_ret = NULL;
	pwd = NULL;
	pwd_ret = getcwd(NULL, 0);
	if (pwd_ret == NULL && errno != ERANGE)
		return (perror("GETCWD : "), 1);
	if (mode == PRINT)
	{
		printf("%s\n", pwd_ret);
		free(pwd);
	}
	if (mode == GET)
		*str = pwd;	
	return (0);	
}
