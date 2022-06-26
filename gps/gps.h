#define MAX_POSITION_LEN 50
#define MODEM "/dev/ttyUSB0"
#define BAUDRATE 115200 

typedef struct {
		char latitude[MAX_POSITION_LEN];
		char longitude[MAX_POSITION_LEN];
} Position;

int serial_port;
char dat;
int flag = 0;
char output_setup[100];
unsigned int i = 0;
Position localPosition;
char w_buff[][256] = {"AT+CGNSPWR=1\r\n", 
					  "AT+CGNSSEQ=\"RMC\"\r\n",
					  "AT+CGNSINF\r\n", 
					  "AT+CGNSURC=2\r\n", 
					  "AT+CGNSTST=1\r\n",
				      "AT+CGNSPWR=0\r\n"};

/**
 * @brief initialize the gps configuration so that we can start receiving data
 *
 * @return 1 if the initialisation is done correctly
 */
int init_gps();

/**
 * @brief extract the latitude and longitude and place them in the structre position
 *
 * @param p position structure where latitude and latitude are gonna be stored
 */
void get_position(Position *p);

/**
 * @brief extract the longitude from the GGA trame and store it in var longitude
 *
 * @param lon_string is the GGA trame received (ex: xxxxxx,xxxxxxx,N,xxxxxx,E,...)
 */
void get_lon(char lon_string[100], char longitude[50]);

/**
 * @brief extract the latitude from the GGA trame and store it in var latitude
 *
 * @param lat_string is the GGA trame received (ex: xxxxxx,xxxxxxx,N,xxxxxx,E,...)
 */
void get_lat(char lat_string[100], char latitude[50]);

/**
 * @brief shift the position of the in the latitude and longitude because they 
 * are not  placed correctly
 */
void format_position();

/**
 * @brief turn off the gps
 */
void close_gps();
