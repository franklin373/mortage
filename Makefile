# Collect information from each module in these four variables.
# Initialize them here as simple variables.
programs := MortageApp
sources :=
libraries :=
extra_clean :=
objects = $(subst .c,.o,$(sources))
dependencies = $(subst .c,.d,$(sources))
include_dirs :=  . include iPhone
#CFLAGS   =  -static -g -O0 -Wall -Wimplicit-function-declaration -Wno-implicit
#CFLAGS   =  -static -g -O0 -Wall -Werror-implicit-function-declaration -Wno-implicit
#CFLAGS   =  -static -g -O0 -Wall -Wno-implicit
CFLAGS   =  -g -O0 -Wall 
CPPFLAGS += $(addprefix -I ,$(include_dirs))
vpath %.h $(include_dirs)
CC       = gcc
MV := mv -f
RM := rm -f
SED := sed
all:

include app/module.mk
#include des/module.mk
#include des/ssl/module.mk
include utils/module.mk
#include protocol/module.mk
include commu/module.mk
include interest/module.mk
include utils_from_payadm/module.mk
include time/module.mk
include event/module.mk
include iterator/module.mk
include time_pivotal/module.mk
#include iPhone/module.mk
#include p25iProcedure/module.mk
#include aes/module.mk

.PHONY: all
all: $(programs)
MortageApp: $(objects) $(libraries)
	gcc $^ -o $@
.PHONY: libraries
libraries: $(libraries)
.PHONY: clean
clean:
	$(RM) $(objects) $(programs) $(libraries) \
		$(dependencies) $(extra_clean)
ifneq "$(MAKECMDGOALS)" "clean"
include $(dependencies)
endif
%.c %.h: %.y
	$(YACC.y) --defines $<
	$(MV) y.tab.c $*.c
	$(MV) y.tab.h $*.h
%.d: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -M $< | \
	$(SED) 's,\($(notdir $*)\.o\) *:,$(dir $@)\1 $@: ,' > $@.tmp
	$(MV) $@.tmp $@
