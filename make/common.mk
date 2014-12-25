AR = gcc
CC = gcc

myDepSuffix := cmdep
myObjSuffix := cmobj

commonSourceDirs := ../common/src/

tempDllCSources := $(foreach dir,$(commonSourceDirs),$(wildcard $(dir)*.c))

dllCSources := $(filter-out $(loadersdkSourceDirs)malloc_with_mempool.c, $(tempDllCSources))
dllCSources += $(thisCSources)

dllCObjs := $(dllCSources:.c=.$(myObjSuffix))

myCSources := $(dllCSources)

myInclude := \
		     -I ../common/inc

myDepCFLAGS := -DTK_FB_BPP=16 \
             -DTK_NO_SEMI_TRANSPARENCY

myCFLAGS := $(subst -D,-D,$(myDepCFLAGS))
#myCFLAGS += //FD //GZ //c //nologo //MDd //W3 //Gm //GX //ZI //Od

#myCFLAGS += //nologo //MTd //W3 //Gm //GX //ZI //Od //FD //GZ //c 
myLinkFLAGS := $(vc6Libs) ../TigerMapEngine/libs/$(tk_platform)/$(myStaticLibName) \
			   //debug //nologo //dll //incremental:yes //pdbtype:sept \
               //machine:I386 //nodefaultlib:"LIBCD.lib" \
               //nodefaultlib:"LIBCMTD.lib" \
               //pdb:"$(myOutputDir)\$(myTargetBaseName).pdb" \
               //out:"$(myOutputDir)\$(myTargetBaseName).dll" \
               //implib:"$(myOutputDir)\$(myTargetBaseName).lib"
root :=$(shell cd ../;pwd)
excludeSources = 

include ../make/base.inc.mk
dirs := $(shell find $(root) -maxdepth 1 -type d)
remake: base.object
	@$(AR)  -o $(myTargetBaseName) $(dllCObjs)
	@echo build completed!
clean:
	rm $(myTargetBaseName) $(myCObjs) $(myCDepends)




cleanall:
	@for subdir in $(dirs); \
	do \
	echo "------------making $@ in $$subdir"; \
	(cd $$subdir;make clean); \
	done
