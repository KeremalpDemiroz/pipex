#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int out = open("optimized/test", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	int a = dup(1);
	dup2(out, 1);
	close(out);
	write(1,"merhaba\n", 8);
	dup2(a, 1);
	close(a);
	write(1, "deneme\n", 7);
}