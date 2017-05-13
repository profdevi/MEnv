#v1.0 copyright Comine.com 20170511R0947
# Simple Make file for nmake
#  -Revised to exclude extra search libraries

OUTPUT=MEnv.exe
LIBS=
CC=cl.exe
CLINKER=link.exe
BASELIBS=
FLAGS=-nologo -DWIN32 -O2 -DNDEBUG -MT -DUNICODE -D_UNICODE -D_CONSOLE -Iinclude -EHsc
CFLAGS=-I . 
CLINKFLAGS=                                 # /NODEFAULTLIB:LIBCMT 
DSNNAME=UnitTest
BUILDDBSQL=dbbuild.tmp
DROPDBSQL=dbdrop.tmp


########### Main.exe ##############
all : ResourceFiles $(OUTPUT)
	@banner "Finished creating $(OUTPUT)"


###################################
ResourceFiles:
	mrcgen -a


############ Compile Object Files ################
.cpp.obj:
	$(CC) -c $(CFLAGS)  $(FLAGS) $**
	-$(CC) -c $(CFLAGS)  $(FLAGS) *.c
	cp setargv.vc14  setargv.obj


############ Compile Object Files ################
.c.obj:
	$(CC) -c $(CFLAGS)  $(FLAGS) $**
	-$(CC) -c $(CFLAGS)  $(FLAGS) *.cpp
	cp setargv.vc14  setargv.obj


########### Compile Resource Files ################
*.res: *.rc
	$(RC) -r $(RCFLAGS) $**


############ Link Object Files  ##################
$(OUTPUT) : *.obj *.res
	$(CLINKER) $(CLINKFLAGS)  $**  $(LIBS)  $(BASELIBS)  -OUT:$@


############# Clean ###############
clean : 
	-rm -f *.obj /q
	

############ Clean All Exe+Objs #######
cleanall:
	-rm -f *.obj 
	-rm -f *.tli
	-rm -f *.tlh
	-rm -f $(OUTPUT)

