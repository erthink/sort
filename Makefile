# Copyright (c) 2010-2014 Christopher Swenson.
# Copyright (c) 2012 Google Inc. All Rights Reserved.

CFLAGS ?= -Ofast -g -Wall -pedantic -Wno-format -Wno-unused-function -ffunction-sections
# -save-temps

EXTRA_OBJ := std_sort.o yysort.o sort_rela589n.o

default: demo stresstest multidemo test

.PHONY: default clean test format

test: stresstest benchmark
	./benchmark | tee benchmark.txt
	./stresstest

clean:
	rm -f demo multidemo stresstest benchmark $(EXTRA_OBJ)

demo: demo.c sort.h extra.h $(EXTRA_OBJ) Makefile
	$(CC) $(CFLAGS) demo.c $(EXTRA_OBJ) -o demo -lstdc++

multidemo: multidemo.c sort.h extra.h $(EXTRA_OBJ) Makefile
	$(CC) $(CFLAGS) multidemo.c $(EXTRA_OBJ) -o multidemo -lstdc++

stresstest: stresstest.c sort.h extra.h $(EXTRA_OBJ) Makefile
	$(CC) $(CFLAGS) $(EXTRA_OBJ) stresstest.c -lstdc++ -o stresstest

#stresstest: stresstest.c sort.h extra.h std_sort.cxx yysort.c Makefile
#	$(CC) $(CFLAGS) std_sort.cxx stresstest.c -lstdc++ -o stresstest

benchmark: benchmark.c sort.h extra.h $(EXTRA_OBJ) Makefile
	$(CC) $(CFLAGS) benchmark.c $(EXTRA_OBJ) -o benchmark -lstdc++

format:
	astyle --options=astyle.options sort.h demo.c multidemo.c stresstest.c benchmark.c extra.h std_sort.cxx yysort.c

std_sort.o: std_sort.cxx extra.h Makefile
	$(CXX) $(CFLAGS) -c $< -o $@

sort_rela589n.o: sort_rela589n.cxx extra.h Makefile
	$(CXX) $(CFLAGS) -c $< -o $@

yysort.o: yysort.c extra.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@
