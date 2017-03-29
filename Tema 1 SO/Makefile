build: tema1.exe 
	
tema1.exe: tema1.obj hashtable.obj bucket.obj hash.lib
	cl hash.lib tema1.obj hashtable.obj bucket.obj
	
tema1.obj:
	cl /c tema1.c

hashtable.obj:
	cl /c hashtable.c

bucket.obj:
	cl /c bucket.c
	
clean:	
	del tema1.exe tema1.obj hashtable.obj bucket.obj
