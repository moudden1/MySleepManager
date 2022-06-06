c=gcc

all : getDataGoogleMaps2.o reveil.c reveil.h getDataMeteo.o affiche_heur.c
	$(c) getDataGoogleMaps2.o reveil.c -lpthread -lcurl -ljson-c -lwiringPi -o reveil
	$(c)  `pkg-config --cflags gtk+-3.0` -o heure getDataMeteo.o affiche_heur.c -lcurl -ljson-c `pkg-config --libs gtk+-3.0`
getDataGoogleMaps2.o : getDataGoogleMaps2.c getDataGoogleMaps2.h
	$(c) -c getDataGoogleMaps2.c
getDataMeteo.o : getDataMeteo.c getDataMeteo.h
	$(c) -c getDataMeteo.c
clean : 
	rm reveil getDataGoogleMaps2.o heure getDataMeteo.o

