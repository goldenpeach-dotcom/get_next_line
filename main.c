#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

static void test_fd(int fd, const char *label)
{
	char	*line;
	int	i = 1;

	printf("---- %s ----\n", label);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("[%d] %s", i, line);
		free(line);
		i++;
	}
	printf("---- END %s ----\n\n", label);
}

int	main(void)
{
	int fd1 = open("test1.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	int fd3 = open("test3.txt", O_RDONLY);

	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		perror("open");
		return (1);
	}
	test_fd(fd1, "FILE 1");
	test_fd(fd2, "FILE 2");
	test_fd(fd3, "FILE 3");
	close(fd1);
	close(fd2);
	close(fd3);

    // 標準入力テスト（必要なら）
    // printf("標準入力から読み込みます。Ctrl+D で終了。\n");
    // test_fd(0, "STDIN");

    return (0);
}
