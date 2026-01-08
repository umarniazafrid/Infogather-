all:
	g++ main.cpp scanner.cpp report.cpp -o infogather++ -pthread

clean:
	rm -f infogather++ *.json
