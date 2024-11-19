


all :
	c++ *.cpp -o wbsv -O3 -g3 -fsanitize=address
	./wbsv