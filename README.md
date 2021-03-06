# mtag

EN: mtag is the command-line tool for media files tagging. It can use the text file template to tag the multiply sets of media files. You can apply the same template for Ogg, MP3, and FLAC album versions. mtag can also extract the tags to the text file and rename files according to their tags.


RU: mtag это утилита для записи тэгов в мультимедийные файлы. mtag использует файл-шаблон с тэгами, который можно применять к нескольким наборам файлов в разных форматах. Иначе говоря, одним шаблоном вы запишете тэги в варианты альбома в MP3, Ogg, FLAC. mtag также умеет извлекать тэги из файлов (в шаблон) и переименовывать файлы на основе записанных в них тэгов.

Usage/Использование:
------------

EN:

**To tag some files**, use the command line:

mtag apply rules_file extension

Example: mtag apply rules.txt ogg

To be tagged correctly, the media files names needs to be named in the alphabetical order, i.e. for example:

```
01-first-song.ogg  
01-second-song.ogg  
01-third-song.ogg  
```

The rules file must be in UTF-8 encoding. The rules file syntax is simple - the set of blocks with tags. Each block is ended with "\#\#\#". Example:

```
#filename: 01-first-song.ogg
@album=testalbum  
@artist=Megapunkers  
@title=song one  
\#\#\#  
#filename: 01-second-song.ogg  
@album=testalbum  
@artist=Megapunkers  
@title=song two  
\#\#\#  
#filename: 01-third-song.ogg  
@album=testalbum  
@artist=Megapunkers  
@title=song three  
\#\#\#
```

So the first block will be applied to the first media file at the current directory, the second block to the second file, etc. 

The list of available tags: @artist, @title, @album, @genre, @comment, @year, @track.

The `#filename` tag in block is ignored, it is needed just to understand which media file tags you edit now. Only the file order in directory and block order in rules file matters, not the `#filename` tag.

**To extract the tags** from the media files to the rules file, use the "extract" option:

mtag extract OUTPUTFILE extension <list_of_required_tags>

For example:

mtag extract RULES ogg

or

mtag extract RULES mp3 "@artist,@genre,@album"

<list_of_required_tags> is an optional parameter, it defines which tags will be generated even if such data is not presented in source media file, blank values will be used.

**To rename files** according their tags, use:

mtag rename "template string" extension

The template string can contain any tags macros (i.e. @artist, @title, etc.), @fname macro for the original file name, and \# as the numbers counter (the count of \# is the leading zeroes count minus 1);

Examples:

mtag rename "\#\# - @title" mp3  
mtag rename "\#\# - @artist - @title" mp3  
mtag rename "\#\# - @fname" mp3  

**To list files tags** by the template, use:

mtag list "template string" extension

Example, write to screen:

mtag list "\#\# - @artist @title" mp3  

Example, write to the file:

mtag list "\#\# - @artist @title" mp3  > file.txt


RU:

**Чтобы записать тэги** в файлы, формат командной строки таков:

mtag apply файл_с_правилами расширение

Пример: mtag apply rules.txt ogg

Звуковые файлы должны быть именованы по алфавиту, например:

```
01-first-song.ogg  
01-second-song.ogg  
01-third-song.ogg
```

Файл правил должен быть в кодировке UTF-8. Синтаксис файла прост - файл состоит из блоков тэгов, и каждый блок оканчивается "\#\#\#". Пример:

```
#filename: 01-first-song.ogg
@album=проба  
@artist=никто  
@title=песенка первая  
\#\#\#  
#filename: 01-second-song.ogg
@album=проба  
@artist=никто  
@title=песенка вторая  
\#\#\#  
#filename: 01-third-song.ogg
@album=testalbum  
@artist=никто  
@title=песня третья  
\#\#\#
```

Первый блок будет применен к первому файлу (с указанным расширением) в текущем каталоге, второй ко второму, и так далее.

Список доступных тэгов: @artist, @title, @album, @genre, @comment, @year, @track.

Тэг `#filename` в блоке игнонируется, он нужен для понимания того какой медиафайл сейчас редактируется. Только порядок файлов в каталоге и тэгов в списке правил влияет на то какой блок тэгов будет применен к какому файлу, тэг `#filename` ни на что не влияет.

**Чтобы извлечь тэги из файлов в файл правил**, к командной строке надо добавить ключик "extract", например:

mtag extract RULES ogg <список_обязательных_тэгов>

или

mtag extract RULES mp3 "@artist,@genre,@album"

<список_обязательных_тэгов> это необязательный параметр, оперделяющий список тэгов, которые будут сгенерированы в файле правил, даже если такие тэги в медиафайле не представлены, значения таких тэгов будут пустыми.

**Чтобы переименовать файлы** согласно записанным в них тэгам, используйте команду:

mtag rename "строка шаблона" расширение

Строка шаблона может содержать любые тэговые макросы (т.е. @artist, @title, и прочие), @fname в качестве заменителя исходного имени файла, и \# как счетчик (количество \# означает число дополяющих нулей).

Примеры:

mtag rename "\#\# - @title" mp3   
mtag rename "\#\# - @artist - @title" mp3  
mtag rename "\#\# - @fname" mp3  


**Для вывода тэгов на экран или в файл**, по шаблону, используйте команду:

mtag list "шаблон" расширение

Пример вывода на экран:

mtag list "\#\# - @artist @title" mp3  

Пример вывода в файл file.txt:

mtag list "\#\# - @artist @title" mp3  > file.txt


Requirements/Зависимости:
------------

Taglib, C++ 11


Installation/Установка:
------------

EN:

As usual, under the root (mtag will be installed to /usr/local/bin):

make  
make install

To uninstall:

make uninstall


RU:

Как обычно, под рутом (mtag будет установлен в /usr/local/bin):

make  
make install

А чтобы удалить:

make uninstall


License/Лицуха
-----------

EN: mtag is public domain.

RU: mtag - общественное достояние.


Credits/Кредиты
------------

Program site/сайт: https://github.com/psemiletov/mtag

Developer/разработчик:
Petr Semiletov <tea@list.ru>, http://semiletov.org
