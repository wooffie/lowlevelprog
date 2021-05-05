.PHONY: test cmd samples uninstall

OBJS= heap.o
RM= del
MAKE= make -s
MYLIBNAME= libHeap.a
NAME=heap.exe

$(MYLIBNAME): $(OBJS)
	$(AR) -rsc $@ $^
	@$(RM) -f $(OBJS)
#	$(RM) -f $(OBJS:.o=.d)	


#-Wno-pedantic-ms-format в попытках избежать конфликтов из-за size_t
CFLAGS= -std=c11 -pedantic -Wall -Wextra

# Включаемые файлы следует искать в каталоге "include"
INCLUDES+= -I./include


# Построение объектных файлов
%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Make должна искать файлы *.h в каталогах include и src
vpath %.h include src
# ..., а файлы *.c - в каталоге src
vpath %.c src

uninstall:
	$(RM) -f $(MYLIBNAME)
	$(RM) -f $(NAME)

test:
	$(MAKE) -C test
	
cmd: libHeap.a
	$(MAKE) -C src
	
$(NAME): cmd
	
samples: $(NAME)
	@echo Working with file "samples/heap"
	@echo Max heap
	@heap.exe -max tree -i samples/heap.txt
	@echo Min heap
	@heap.exe -min tree -i samples/heap.txt
	@echo Sotring data from heap
	@heap.exe sort -i samples/heap.txt
	@echo Extract max key from heap and write to "samples/heap1.txt"
	@heap.exe -max extract -i samples/heap.txt -o samples/heap1.txt
	@echo Extract min key from heap and write to "samples/heap1.txt"
	@heap.exe -min extract -i samples/heap1.txt -o samples/heap1.txt
	@echo Tree for new heap
	@heap.exe -max tree -i samples/heap1.txt
#	$(RM) -f samples/heap1.txt
	
-include $(OBJS:.o=.d)
