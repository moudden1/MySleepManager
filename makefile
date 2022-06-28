c=gcc

all : build/getDataGoogleMaps2.o src/reveil.c build/getDataMeteo.o src/affiche_heur.c build/alarm_graph.o build/gps.o
	$(c) `pkg-config --cflags gtk+-3.0` -I./include -o bin/reveil build/getDataGoogleMaps2.o build/alarm_graph.o src/reveil.c -lpthread -lcurl -ljson-c -lwiringPi -lmosquitto build/gps.o `pkg-config --libs gtk+-3.0`
	$(c)  `pkg-config --cflags gtk+-3.0` -o bin/heure build/getDataMeteo.o src/affiche_heur.c -lcurl -ljson-c -lwiringPi `pkg-config --libs gtk+-3.0`
build/getDataGoogleMaps2.o : src/getDataGoogleMaps2.c 
	$(c) -I./include -c src/getDataGoogleMaps2.c -o build/getDataGoogleMaps2.o
build/getDataMeteo.o : src/getDataMeteo.c 
	$(c) -I./include -c src/getDataMeteo.c -o build/getDataMeteo.o
build/alarm_graph.o : src/alarm_graph.c
	$(c) -I./include -c `pkg-config --cflags gtk+-3.0` src/alarm_graph.c -o build/alarm_graph.o
build/gps.o: src/gps.c 
	$(c) -Wall -g -c src/gps.c -o build/gps.o
clean : 
	rm bin/* build/*

