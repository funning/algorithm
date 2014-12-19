myCObjs := $(myCSources:.c=.$(myObjSuffix))

myCDepends := $(myCSources:.c=.$(myDepSuffix))

myGccDepInclude := $(subst -J,-I,$(myInclude))

$(myCDepends): %.$(myDepSuffix): %.c
	@echo "generating $*.$(myDepSuffix)" 
	@gcc -MM $(myDepCFLAGS) $(myGccDepInclude) $< | sed 's,$(basename $(@F))\.o,$*\.$(myObjSuffix) $*\.$(myDepSuffix),' > $@
	

include $(myCDepends)

base.object: $(myCObjs)

$(myCObjs): %.$(myObjSuffix): %.c
	@echo "compiling $*.c"
	@echo "$(CC) $(myCFLAGS) $(myInclude) -c $< -o $@"
	@$(CC) $(myCFLAGS) $(myInclude) -c $< -o $@
