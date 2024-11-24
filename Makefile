


all :
	@c++ -std=c++11 *.cpp -o wbsv -O3 -g3 -fsanitize=address
	-@./wbsv
	@echo
	@echo

