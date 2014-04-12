bin_PROGRAMS=scsb101
scsb101_SOURCES= $(SOURCES)

SOURCES = 						\
	sbus_sc_V101.cpp 			\
	sbsc_application.cpp		\
	sbsc_combinator.cpp			\
	sbsc_node.cpp				\
	sbsc_sbus.cpp				\
	sbsc_sbuf.cpp				\
	sbsc_itap.cpp				\
	sbsc_otap.cpp				\
	sbsc_alu_4op.cpp			\
	sbsc_alu_mx4.cpp			\
	sbsc_alu_inc.cpp			\
	sbsc_conduit_simple.cpp		\
	sbsc_conduit_fifo.cpp		
	
scsb101_CPPFLAGS = -I/usr/local/eda/sysc230/include -I/usr/include/c++/4.6.3 -I/usr/include	-std=c++11 -std=gnu++11
scsb101_LDFLAGS = -L/usr/lib64 -L/usr/local/eda/sysc230/lib-linux64 -L/usr/lib64 -lsystemc -lm -std=c++11 -std=gnu++11
