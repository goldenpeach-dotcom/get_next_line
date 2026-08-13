#include "get_next_line.h"

/*改行が来るまでファイルを読み込み静的変数に結合し続ける*/
static char *read_file(int fd, char *save)
{
	char	*buf;
	ssize_t	r_bytes;

	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (ft_free(&save));
	r_bytes = 1;
	while (!ft_strchr(save, '\n') && r_bytes > 0)
	{
		r_bytes = read(fd, buf, BUFFER_SIZE);
		if (r_bytes == -1)
			return (free(buf), ft_free($save));
		buf[r_bytes] = '\0';
		save = ft_strjoin(save, buf);
		if (!save)
			return (free(buf), NULL);
	}
	free(buf);
	return(save);
}

/*静的変数から次の一行（開業を含む）を切り出す*/
static char	*extract_line(char *save)
{
	char	*line;
	size_t	i;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	line = ft_substr(save, 0, i);
	return (line);
}

/*静的変数から出力した一行分を削除して残りを保存する*/
static char	*recreate_save(char *save)
{
	char	*new_save;
	size_t	i;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
		return (ft_free(&save));
	new_save = ft_substr(save, i + 1, ft_strlen(save + i + 1));
	ft_free(&save);
	return (new_save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_file(fd, save);

}