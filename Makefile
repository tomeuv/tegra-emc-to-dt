print-emc-timings: print-emc-timings.c board-ardbeg-memory.c
	gcc print-emc-timings.c -o print-emc-timings

clean:
	rm print-emc-timings

test: print-emc-timings
	./print-emc-timings
