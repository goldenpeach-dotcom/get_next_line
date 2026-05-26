#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		line_count;

	if (argc < 2)
	{
		fd = 0;
		printf("--- [標準入力から読込中...] (Ctrl+D で終了) ---\n");
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			perror("ファイルが開けませんでした");
			return (1);
		}
		printf("--- [ファイル: %s から読込中...] ---\n", argv[1]);
	}
	line_count = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("[%02d]: %s", line_count++, line);
		free(line);
	}
	printf("\n--- [読込終了 / EOFに到達] ---\n");
	if (fd != 0)
		close(fd);
	return (0);
}
