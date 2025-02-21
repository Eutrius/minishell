#include <stdio.h>
#include "../libft/libft.h"
#include <unistd.h>


void find_guard(char *content)
{
  int i = 0;
  int j = 0;
  while(content[i])
  {
    if (content[i] == '\\' && content[i + 1] == '\\')
    {
      content[j] = '\\';
      i+=2;
    }
    else if (content[i] == '\\' && content[i + 1] != '\\')
      i++;
    else
    {
      content[j] = content[i];
      i++;
      j++;
    }
  }
  content[j] = '\0';
}


int	is_builtin(char *buf)
{
	if (!ft_strcmp(buf, "echo"))
		return (1);
	if (!ft_strcmp(buf, "cd"))
		return (1);
	if (!ft_strcmp(buf, "pwd"))
		return (1);
	if (!ft_strcmp(buf, "export"))
		return (1);
	if (!ft_strcmp(buf, "unset"))
		return (1);
	if (!ft_strcmp(buf, "env"))
		return (1);
	if (!ft_strcmp(buf, "exit"))
		return (1);
	return (0);
}
