c=gcc

all : getDataGoogleMaps2.o src/reveil.c  getDataMeteo.o src/affiche_heur.c alarm_graph.o
	$(c) `pkg-config --cflags gtk+-3.0` -I./include -o reveil getDataGoogleMaps2.o alarm_graph.o src/reveil.c -lpthread -lcurl -ljson-c -lwiringPi -lmosquitto `pkg-config --libs gtk+-3.0`
	$(c)  `pkg-config --cflags gtk+-3.0` -o heure getDataMeteo.o src/affiche_heur.c -lcurl -ljson-c -lwiringPi `pkg-config --libs gtk+-3.0`
getDataGoogleMaps2.o : src/getDataGoogleMaps2.c 
	$(c) -I./include -c src/getDataGoogleMaps2.c
getDataMeteo.o : src/getDataMeteo.c 
	$(c) -I./include -c src/getDataMeteo.c
alarm_graph.o : src/alarm_graph.c
	$(c) -I./include -c `pkg-config --cflags gtk+-3.0` src/alarm_graph.c 
clean : 
	rm reveil getDataGoogleMaps2.o heure getDataMeteo.o alarm_graph.o

