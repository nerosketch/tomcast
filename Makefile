CC = cc
STRIP = strip
CROSS := $(TARGET)
CFLAGS := -O2 -ggdb -pipe \
 -W -Wall -Wextra \
 -Wshadow -Wformat-security -Wstrict-prototypes \
 -Wredundant-decls -Wold-style-definition
RM = /bin/rm -f
Q = @

LIBS = -lpthread
FUNCS_DIR = libfuncs
FUNCS_LIB = $(FUNCS_DIR)/libfuncs.a

tomcast_OBJS =  tomcast.o web_pages.o web_server.o igmp.o $(FUNCS_LIB)

all: tomcast

$(FUNCS_LIB):
	$(Q)echo "  MAKE	$(FUNCS_LIB)"
	$(Q)$(MAKE) -s -C $(FUNCS_DIR)

tomcast: $(tomcast_OBJS)
	$(Q)echo "  LINK	tomcast"
	$(Q)$(CROSS)$(CC) $(CFLAGS) $(tomcast_OBJS) $(LIBS) -o tomcast

%.o: %.c
	$(Q)echo "  CC	tomcast		$<"
	$(Q)$(CROSS)$(CC) $(CFLAGS)  -c $<

strip:
	$(Q)echo "  STRIP	tomcast"
	$(Q)$(CROSS)$(STRIP) tomcast

clean:
	$(Q)echo "  RM	$(tomcast_OBJS)"
	$(Q)$(RM) $(tomcast_OBJS) tomcast *~

distclean: clean
	$(Q)$(MAKE) -s -C $(FUNCS_DIR) clean
