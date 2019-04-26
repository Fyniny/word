processor=IDProcessor.o INTProcessor.o OperatorProcessor.o BorderProcessor.o STRINGProcessor.o
processorsource=afx.h table.h wordItem.h IDProcessor.cpp afx.o INTProcessor.cpp OperatorProcessor.cpp BorderProcessor.cpp STRINGProcessor.cpp
obj=main.o table.o wordItem.o afx.o $(processor)
wordmachine: $(obj)
	g++ -o wordmachine $(obj)

main.o : afx.h main.cpp table.h scan.h wordItem.h
	g++ -c main.cpp

table.o : table.h table.cpp wordItem.h afx.h
	g++ -c table.cpp

wordItem.o : table.h wordItem.cpp wordItem.h
	g++ -c wordItem.cpp	

$(processor) : $(processorsource)

afx.o : afx.h afx.cpp
	g++ -c afx.cpp
clean :
	rm $(obj)