


all :
	@c++ -std=c++11 *.cpp -o wbsv -O3 -g3 -fsanitize=address
	@echo Servers is runing 
	@./wbsv
	@echo

