#define MAX_POSITION_LEN 50
#define MODEM "/dev/ttyUSB0"
#define BAUDRATE 115200 

typedef struct {
		char latitude[MAX_POSITION_LEN];
		char longitude[MAX_POSITION_LEN];
} Position;



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

/**
 * @brief uses a math formula to calculate latitude 
 *
 * @param latitude_string : the latitude that we get from the NMEA sentence
 * @param latitude : the string where we store the final latitude
 */
void calculate_latitude(char latitude_string[50], latitude[50]);

/**
 * @brief use a math formula to calculate longitude
 *
 * @param longitude_string : the longitude that we get from the NMEA sentence
 * @param longitude : the string where we store the final longitude
 */
void calculate_longitude(char longitude_string[50], longitude[50]);


