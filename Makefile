# Copyright (c) 2010-2014 Christopher Swenson.
# Copyright (c) 2012 Google Inc. All Rights Reserved.

CFLAGS ?= -O3 -g -Wall -std=c89 -pedantic -Wno-long-long -Wno-format

EXTRA_OBJ := std_sort.o yysort.o

default: demo stresstest multidemo test

.PHONY: default clean test format

test: stresstest benchmark
	./benchmark | tee benchmark.txt
	./stresstest

clean:
	rm -f demo multidemo stresstest benchmark $(EXTRA_OBJ)

demo: demo.c sort.h extra.h $(EXTRA_OBJ)
	$(CC) $(CFLAGS) demo.c $(EXTRA_OBJ) -o demo -lstdc++

multidemo: multidemo.c sort.h extra.h $(EXTRA_OBJ)
	$(CC) $(CFLAGS) multidemo.c $(EXTRA_OBJ) -o multidemo -lstdc++

stresstest: stresstest.c sort.h extra.h $(EXTRA_OBJ)
	$(CC) $(CFLAGS) stresstest.c $(EXTRA_OBJ) -o stresstest -lstdc++

benchmark: benchmark.c sort.h extra.h $(EXTRA_OBJ)
	$(CC) $(CFLAGS) benchmark.c $(EXTRA_OBJ) -o benchmark -lstdc++

format:
	astyle --options=astyle.options sort.h demo.c multidemo.c stresstest.c benchmark.c extra.h std_sort.cxx yysort.c

std_sort.o: std_sort.cxx extra.h
	$(CXX) $(CFLAGS) -c $< -o $@

yysort.o: yysort.c extra.h
	$(CC) $(CFLAGS) -std=c99 -c $< -o $@
