#"Переменные, помеченные export , доступны только оболочкам, запущенным для
#  команд рецепта (команд, которые являются частью правил)"

# Другими словами, при запуске других мейкфайлов из этого, все переменные помеченные
# ключевым словом EXPORT доступны к использованию

# Имя программы/библиотеки
export NAME=Heap

# Параметры для компилятора
# Стандарт языка СИ 11 года, агрегаторы предупреждений и указание папки, где следует искать хедеры
export CFLAGS= -std=c11 -Wall -pedantic -Wextra -I../include

# Выбор компилятора (у нас GNU CC :) )
export CC=gcc

# Для удаления файлов
export RM=del -f


# Флаги для сборщика библиотеки	
# r - Вставляет файлы в архив (с замещением)
# s - Записывает индекс объектного файла в архив или, если он существует, обновляет его, даже если нет других изменений в архиве
# Как я понял флаг s нужен для того, чтобы обновлять библиотеку тольк при обновлении объектных файлов
# с - Создание архива
export ARFLAGS=rsc

# Указываем что цель build - фиктивная, указывает, что цель не связана с файлами
.PHONY: build

# В убогой cmd винды или во всяких шелах не получилось нормально двигать файлами без миллиона костылей, так что без установки библиотеки в проект сегодня

# Т.к. цель build объявлена первой, то при обычным вызове мейк-файла будет исполняться именно она

# Build - собрать статически-линкуемую библиотеку в каталоге src
# Вызываем мейк-файл в каталоге src
build:

	$(MAKE) -C src

.PHONY: app

# App - скомпилировать программу с использованием нашей библиотеки
# Перемещает exe в корневую папку проекта для удобства

app:
	$(MAKE) -C src $(NAME)
	
.PHONY: demo

# Demo - запустить демонстрационную программу
# Выглядит страшно, но пойдёт

demo: app
	@echo Working with file "samples/heap"
	@echo Max heap
	@heap.exe -max tree -i samples/heap.txt
	@echo.
	@echo Min heap
	@heap.exe -min tree -i samples/heap.txt
	@echo.
	@echo Sotring data from heap
	@heap.exe sort -i samples/heap.txt
	@echo.
	@echo Extract max key from heap and write to "samples/heap1.txt"
	@heap.exe -max extract -i samples/heap.txt -o samples/heap1.txt
	@echo.
	@echo Extract min key from heap and write to "samples/heap1.txt"
	@heap.exe -min extract -i samples/heap1.txt -o samples/heap1.txt
	@echo.
	@echo Tree for new heap
	@heap.exe -max tree -i samples/heap1.txt

.PHONY: test

# Test - запустить модульные тесты и вывести результат на консоль

test:
	$(MAKE) -C test

.PHONY: clean

# Clean - удаление всех файлов сгенерированных в процессе работы мейк-файлов и компилятора
# Вызывается во всех папках, где есть мейк-файлы

clean:
	$(RM) $(NAME).exe
	$(MAKE) -C src clean
	$(MAKE) -C test clean