local_dir := app
#local_lib := $(local_dir)/libcodec.a
local_lib := 
local_src := $(addprefix $(local_dir)/,mortageApp.c mortageStep.c mortageCircle.c debt.c )
local_objs := $(subst .c,.o,$(local_src))
libraries += $(local_lib)
sources += $(local_src)
$(local_lib): $(local_objs)
	$(AR) $(ARFLAGS) $@ $^