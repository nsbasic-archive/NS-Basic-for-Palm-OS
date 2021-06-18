CC = m68k-palmos-gcc
AS = m68k-palmos-as
RC = pilrc
CFLAGS = -Wall -O2 -DCOMPILING_LIB

TcpIpLib.prc: TcpIpLib.def TcpIpLib TcpIpLib.ro
	build-prc -o $@ $^

TcpIpLib: TcpIpLib.o TcpIpLib-dispatch.o
	$(CC) -nostartfiles -o $@ $^

TcpIpLib.o: TcpIpLib.c TcpIpLib.h

clean:
	rm -f *.o *.ro TcpIpLib

%-dispatch.s: %.def
	m68k-palmos-stubgen $^

%.ro: %.res
	$(RC) -ro -o $@ $^ |:
