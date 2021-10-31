cxx = g++ -g -Wall

rsa: rsa.o
	$(cxx) $^ -o $@
	
rsa.o: rsa.cpp
	$(cxx) $^ -c -o $@

.PHONY: clean
clean:
	rm -rf rsa.o
	rm -rf rsa