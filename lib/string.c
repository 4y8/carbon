#include <string.h>

int
strlen(char *s)
{
	int len;

	for (len = 0; *s != '\0'; ++s)
		++len;
	return len;
}

int
streq(char *s1, char *s2)
{
	do
		if (*(s1++) != *(s2++))
			return 0;
	while (*s1 != '\0');
	return 1;
}
