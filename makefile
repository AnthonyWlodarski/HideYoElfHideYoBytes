HideYoElfHideYoBytes: HideYoElfHideYoBytes.o
	cc -o HideYoElfHideYoBytes HideYoElfHideYoBytes.o

HideYoElfHideYoBytes.o: HideYoElfHideYoBytes.c
	cc -c HideYoElfHideYoBytes.c

clean:
	rm HideYoElfHideYoBytes HideYoElfHideYoBytes.o
