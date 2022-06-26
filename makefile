c=gcc

all : getDataGoogleMaps2.o reveil.c  getDataMeteo.o affiche_heur.c alarm_graph.o
	$(c) `pkg-config --cflags gtk+-3.0` -I./include -o reveil getDataGoogleMaps2.o alarm_graph.o reveil.c -lpthread -lcurl -ljson-c -lwiringPi -lmosquitto `pkg-config --libs gtk+-3.0`
	$(c)  `pkg-config --cflags gtk+-3.0` -o heure getDataMeteo.o affiche_heur.c -lcurl -ljson-c -lwiringPi `pkg-config --libs gtk+-3.0`
getDataGoogleMaps2.o : getDataGoogleMaps2.c 
	$(c) -I./include -c getDataGoogleMaps2.c
getDataMeteo.o : getDataMeteo.c 
	$(c) -I./include -c getDataMeteo.c
alarm_graph.o : alarm_graph.c
	$(c) -I./include -c `pkg-config --cflags gtk+-3.0` alarm_graph.c 
clean : 
	rm reveil getDataGoogleMaps2.o heure getDataMeteo.o alarm_graph.o

