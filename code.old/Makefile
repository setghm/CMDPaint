APPNAME=PixelPaint
CC=cl.exe
LINK=link.exe
RM=del
LIBRARIES=user32.lib gdi32.lib kernel32.lib
OUTDIR=build
SRC=$(wildcard src/core/*.c) $(wildcard src/controls/*.c) $(wildcard src/*.c)
OBJ=$(subst .c,.obj,$(SRC))

all: $(APPNAME).exe

$(APPNAME).exe: $(OBJ)
	$(LINK) $(notdir $^) /OUT:$(OUTDIR)\$@ $(LIBRARIES)
	$(RM) $(notdir $^)

$(OBJ): %.obj: %.c
	$(CC) /c $< /Fo $(notdir $@)

.PHONY: clean
clean:
	del $(OUTDIR)\$(APPNAME).exe
