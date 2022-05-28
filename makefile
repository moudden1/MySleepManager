c=gcc

all : getDataGoogleMaps2.o reveil.c
	$(c) getDataGoogleMaps2.o reveil.c -lpthread -lcurl -ljson-c -o reveil
getDataGoogleMaps2.o : getDataGoogleMaps2.c getDataGoogleMaps2.h
	$(c) -c getDataGoogleMaps2.c 
clean : 
	rm reveil getDataGoogleMaps2.o


