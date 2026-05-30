*This project has been created as part of the 42 curriculum by mkaneko.*
# get_next_line

## Description
Repeated calls to my get_next_line() function (for example, inside a loop) allow reading a text file pointed to by a file descriptor, one line at a time.

This program returns a single line read from the file descriptor passed as an argument.

By calling the function repeatedly, you can read and return one line at a time from a text file or from standard input.

### Details of the Algorithm and Data Structures
#### Overall Processing Flow
At compile time, specify the buffer size using the -D flag, or use the default value defined in the header file if no flag is provided:
```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c \
   get_next_line.c get_next_line_utils.c get_next_line.h
```

Define static variables (static char *save, static size_t al_size) to preserve data between function calls.

- Return NULL in the following error cases:

	(1) The file descriptor is less than 0

	(2) BUFFER_SIZE is 0

	(3) After executing read_and_join (see below), no valid save exists

If save is empty or contains no newline, read from the file and append the data (read_and_join).

If save contains data after read_and_join, extract the next line and update save (cut_line_update_save).

```text
┌──────────────────────────────┐
│        get_next_line()       │
└───────────────┬──────────────┘
                │
                ▼
        Is there data in save?
                │
        ┌───────┴────────┐
        │ YES             │ NO
        ▼                 ▼
   Use save           Read from fd
        │                 │
        └──────┬─────────┘
               ▼
   save = read_and_join(save, buf)
               │
               ▼
   Does save contain a newline?
        ┌───────┬────────┐
        │ YES    │ NO     │
        ▼        ▼
 line = cut_line_update_save(save)
 save = cut_line_update_save(save)
 return line

(If NO, continue reading)

EOF (read = 0):
 line = save
 save = NULL
 return line
 ```

##### Optional: Function Overview
 - read_and_join(save, buffer)

	Reads from the file descriptor into buffer, then concatenates the new data to save.
	If necessary, reallocates memory to expand save.
	Returns the updated save.

 - cut_line_update_save(save)

	Extracts one line (up to and including the newline) from save and returns it.
	Updates save to contain only the remaining data after the extracted line.
	Frees the old save and replaces it with the new one.

 - extend_save(save, c_len, n_len, al_size)

	Expands the memory area of save when the amount of new data to be added exceeds the currently allocated size.
	The allocation size is doubled, or if that is still insufficient, a larger size of n_len + BUFFER_SIZE + 1024 is allocated.
	The contents of the old save are copied into the new memory area, the old save is freed, and the new save is returned.

 - append_buf(save, buf, s_len, r_bytes)

	Appends the contents of buf (read by read()) to the end of save.
	If a newline character \n is detected during the append operation, a flag is set so that the next step can extract a complete line.
	After copying, the length of save (s_len) is updated, and the function returns whether a newline was included.
------------------------------------------------------------------------------------------------
#### Data Structures Used
• Static Variables
Static variables retain their values even after the function returns, allowing the next call to get_next_line() to continue processing from where it left off.

read() reads only BUFFER_SIZE bytes at a time, which may end in the middle of a line.
Additionally, any characters after a newline must be preserved for the next call.
These “leftover” characters are stored in the static variable save.

Example:

1st call → leftover stored in save

2nd call → processing continues from save

3rd call → new leftover stored in save

• buffer (temporary read buffer)
A local array of size BUFFER_SIZE + 1 used for each read() call.
Unlike static variables, it is destroyed when the function returns.
The data read into buffer is appended to save and then discarded.

• line (dynamically allocated return value)
A dynamically allocated string that stores one complete line to return to the caller.
It is created by extracting characters from the beginning of save up to the newline.

• Dynamic Memory Management (malloc / free)
To reduce the number of memory allocations:

Allocate BUFFER_SIZE + 1 bytes before reading

If read_length + existing_save_length exceeds the current allocation, expand the memory (doubling strategy)

The length of save is tracked and updated each time data is written into line.
After joining new data into save (read_and_join), the temporary buffer is freed.
When updating save (cut_line_update_save), the old save is freed and replaced with the new one.

All unnecessary memory is freed at the end of each function to prevent memory leaks.

#### Design Justification
•Why use a static variable (save)?  
get_next_line must return one line at a time, but read() may stop in the middle of a line.
Only a static variable can preserve leftover data between function calls, making it essential for correct behavior.

•Why separate buffer and save?  
buffer is overwritten on every read(), so persistent data must be stored in save.
This separation clarifies responsibilities:

buffer: temporary read storage

save: persistent storage, concatenation, and line extraction

•Why use dynamic memory (malloc)?  
The length of each line is unknown until runtime.
Dynamic allocation allows returning lines of any length.
Doubling the allocation size reduces the number of reallocations and improves performance.

•Why update save after extracting a line?  
After returning a line, the consumed portion must be removed.
Otherwise, the same line would be returned repeatedly.
Thus:

Extract the line

Store the remaining data in a new save

•Why the order: read → join → newline check?  
This ensures:

Reading continues until a newline appears

save always contains the latest data

The function can return a line as soon as a newline is found

•Why return save at EOF?  
If read() returns 0 but save still contains data, that data represents the final line—even if it lacks a trailing newline.

## Instruction
•Required Files
To use this project, include the following three files:

get_next_line.c

get_next_line_utils.c

get_next_line.h

•Usage
Include the header and call get_next_line() to read one line at a time from a file descriptor.

```
#include "get_next_line.h"

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
}
```
### Compilation
You can specify BUFFER_SIZE at compile time:

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c \
    get_next_line.c get_next_line_utils.c
```
##### Return Value Specification
Returns one line (including the newline character)

Returns the last line even if it does not end with a newline

Returns NULL when there is nothing left to read

Returns NULL on error

#### Notes
Always free() the returned string

Returns NULL if the file descriptor is invalid or if BUFFER_SIZE ≤ 0

## Resources
man pages (read, malloc, free)

苦しんで覚えるC言語 (MMGames)

新・明解C言語 入門編 (柴田望洋)

### Use of AI
Asked for advice on how read works, how to use static variables, and how to optimize processing.

Helped refine the structure of the README and translate it into English.

-------------------------------------------------------------------------------------------------

## 概要説明

- このプログラムは、引数として与えられたファイルディスクリプタから読みとった一行を返すプログラムです。
- ループを使うなどして繰り返し呼び出すことで、ファイルディスクリプタが指すテキストファイルや標準入力から１行ずつ読み込んで返すことができます。

### アルゴリズムとデータ構造の詳細

#### 全体の処理の流れ
1.コンパイル時に以下のように指定するか、-Dフラグを使わないときは、ヘッダーファイルで既に指定されたバッファーサイズでreadする。
	cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c

2.静的変数（static char save,static size_t al_size）を定義しておく。

3.以下の場合はエラーとしてNULLを返す。
	(1)ファイルディスクリプタが０未満の時
	(2)バッファーサイズが０の時
	(3)read_and_join（以下参照）の実行後にsaveがない時

4.saveにデータがないか改行がないときは、readしてデータを結合する（read_and_join）

5.read_and_joinの結果、saveにデータがあれば、出力するデータを作り返す(cut_line_update_save)

```text
┌──────────────────────────────┐
│        get_next_line()       │
└───────────────┬──────────────┘
                │
                ▼
        save にデータはある？
                │
        ┌───────┴────────┐
        │ YES             │ NO
        ▼                 ▼
 save を使う           read する
        │                 │
        └──────┬─────────┘
               ▼
     save = read_and_join(save, buf)
               │
               ▼
     save 内に改行がある？
        ┌───────┬────────┐
        │ YES    │ NO     │
        ▼        ▼
 line = cut_line_update_save(save)
 save = cut_line_update_save(save)
 return line

（NO の場合は read を繰り返す）

EOF（read=0）なら：
 line = save
 save = NULL
 return line
```

##### Optional: Function Overview（そのほかの関数の概要）
- read_and_join(save, buffer)

	ファイルディスクリプタから buffer にデータを読み込み、
	その新しいデータを save に結合します。
	
	必要に応じて、save のメモリ領域を再確保して拡張します。
	更新された save を返します。

- cut_line_update_save(save)

	save の先頭から改行文字まで（改行を含む）を 1 行として切り出し、その行を返します。
	
	同時に、切り出した部分を除いた残りのデータだけを新しい save として更新します。
	
	古い save は free し、新しい save に置き換えます。

- extend_save(save, c_len, n_len, al_size)

	save に新しく追加するデータ量が現在の確保サイズを超える場合に、save のメモリ領域を拡張します。

	確保サイズを 2 倍にするか、必要に応じて n_len + BUFFER_SIZE + 1024 の余裕を持ったサイズを確保します。
	
	古い save を新しい領域にコピーし、free した後、新しい save を返します。

- append_buf(save, buf, s_len, r_bytes)

	read() で読み込んだ buf の内容を save の末尾に追加します。
	
	追加中に改行文字 \n を検出した場合はフラグを立て、後続処理で行の切り出しができるようにします。
	
	コピー後、save の長さ（s_len）を更新し、改行が含まれていたかどうかを返します。

#### 使用しているデータ構造
- static (静的変数)
	static を付けた変数は、関数を抜けても値が保持されるため、次回の get_next_line 呼び出しでも前回の続きから処理できます。

	read は BUFFER_SIZE 分だけ読み込みますが、行の途中で終わることがあり、また改行より後ろのデータが余ることがあります。
	
	これらの「余り」を static 変数に保存することで、次回の呼び出し時に再利用できます。
	
	（例）

	1 回目の呼び出し → 余りを save に保存

	2 回目の呼び出し → save の続きから処理

	3 回目の呼び出し → 新しい余りを save に保存

- buffer（読み込み用バッファ）  
	read で毎回読み込む一時領域で、BUFFER_SIZE + 1 のローカル配列です。

	static 変数とは異なり、関数を出ると破棄されるため、
	読み込んだデータは save（静的変数）に結合して保持します。
	
	read の戻り値とセットで扱い、読み込みが終わったら不要になります
	
- line（返す行を構築する動的メモリ）  
	呼び出し側に返す 1 行分の文字列を格納するために malloc で確保します。
	save の先頭から改行までを切り出して line を作成し、返却します。

- 文字列操作のための動的メモリ管理（malloc / free の方針）  
	メモリ確保の回数を減らして処理を軽くするため、

	read 前に BUFFER_SIZE + 1 分のメモリを確保

	「read で読み込んだ長さ + save に残っているデータの長さ」が現在の確保サイズを超える場合は、必要に応じてメモリを拡張（2 倍確保）
	といった方針で管理しています。

	save の長さを常に記録しておき、line に書き出すたびに更新して整合性を保ちます。
	read したデータを save に結合した後（read_and_join）、buffer の領域は free します。
	また、cut_line_update_save で save を更新する際には、古い save を free してから新しい save に置き換えています。

	各関数の終了時に不要になったメモリを free することで、メモリリークを防いでいます。
	ただし、書き出した行(line)の領域のfreeは、呼び出し側（main関数）で行います。


#### 設計の正当化

1. static 変数（save）を使用する理由
get_next_line は「1 行ずつ返す」関数であり、
read が行の途中で終わることがあるため、前回の余りを保持する必要がある。
関数をまたいでデータを保持できるのは static だけであり、
この要件を満たすために static を採用した。

2. buffer と save を分離した理由
buffer は read のたびに上書きされる一時領域であり、
行の途中で終わる可能性があるため、永続的に保持すべきデータは save に保存する必要がある。
この分離により、

	buffer は「読み込み専用」

	stash は「保持・結合・切り出し」

	という役割が明確になり、処理が安定する。

3. 動的メモリ（malloc）を使用する理由
返す行の長さは実行時まで分からないため、
固定長配列では対応できない。
そのため、必要な長さだけ動的に確保する設計を採用した。
また、メモリを 2 倍ずつ拡張する方式を採用することで、
再確保の回数を減らし、パフォーマンスを向上させている。

4. save の更新（cut_line_update_save）を行う理由
1 行を返した後、save の先頭には「返した部分」が残る。
これを毎回削除しておかないと、
次回の呼び出しで同じ行を返してしまう。
そのため、

	line を切り出す

	残りを新しい save として保存する
という処理が必要になる。

5. read → join → 改行チェック の順にした理由
この順番にすることで、

	改行が出るまで読み込みを続けられる

	save に常に最新のデータが溜まる

	改行が見つかった瞬間に line を返せる

	という、get_next_line の仕様に最も適した動作になる。

6. EOF の扱いを save ベースにした理由
read が 0 を返した場合でも、
save にデータが残っていればそれは「最後の行」である。

	save をそのまま返すことで、
ファイル末尾の行が改行で終わっていない場合にも対応できる。

## instruction
■ 必要なファイル
	本プロジェクトを使用するには、以下の 3 ファイルをプロジェクトに追加してください。

	get_next_line.c

	get_next_line_utils.c

	get_next_line.h

■ 使用方法
	get_next_line.h を include し、get_next_line() を呼び出すことで、
	指定したファイルディスクリプタから 1 行ずつ読み取ることができます。

```	c
#include "get_next_line.h"

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
}
```
■ コンパイル方法
	BUFFER_SIZE はコンパイル時に指定できます。指定しない場合は　10　となります。

```コード
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c \
    get_next_line.c get_next_line_utils.c
```
■ 返り値の仕様
	読み込んだ 1 行を返す（改行を含む）

	ファイル末尾の行が改行で終わっていなくても返す

	読み込むものがなくなったら NULL を返す

	エラー時も NULL を返す

■ 注意点
	返された文字列は必ず free() してください

	無効な fd や BUFFER_SIZE ≤ 0 の場合は NULL を返します

## Resources

- man page (read malloc free)
- 「苦しんで覚えるC言語」MMGames:著
- 新・明解C言語　入門編　柴田望洋著

### AIの使用
- readの動きと静的変数の使い方、処理をより軽くする方法についてアドバイスを求めた。
- README.mdの形をきれいに整えてもらい、英訳してもらった。