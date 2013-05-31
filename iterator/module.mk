local_dir := iterator
#local_lib := $(local_dir)/libcodec.a
local_lib := 
local_src := $(addprefix $(local_dir)/,iter_deduction_ahead.c iter_deduction_regu_raw.c iter_deduction_regu.c iter_intr_adj.c iter_event.c iter_file.c iter_facade.c )
local_objs := $(subst .c,.o,$(local_src))
libraries += $(local_lib)
sources += $(local_src)
$(local_lib): $(local_objs)
	$(AR) $(ARFLAGS) $@ $^