cc=g++
dir=/work/rws/file

b:a

a:a.o f.o
	rm -f $@
	$(cc) $^ -o $@ -I $(dir)
	rm *.o

a.o:a.cpp
	rm -f $@
	$(cc) -c $< -I $(dir)
f.o:
	rm -f $@
	$(cc) -c $(dir)/JFile.cpp -o $@
