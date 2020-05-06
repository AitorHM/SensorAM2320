/********************************************************************************
*								 DSE	2020									*
*						Mario Ocampo Y Aitor Hernández 							*
*						  Práctica 1. Sensor AM2320								*
*																				*
*********************************************************************************/
#include <unistd.h>			//Needed for I2C port
#include <fcntl.h>			//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include "stdio.h"
#include "stdint.h"
#include "signal.h"


int run = 1;

void handler(int signal){

      run = 0;
	
}
	
	//----- OPEN THE I2C BUS -----
int main(void){

	int file_i2c; 
	int addr = 0x5c;  //The I2C address of the slave
	char letra;
	char fpad[12];
	uint8_t buf[8];
	uint16_t humedad_t;
	uint16_t temperatura_t;
	int error=0;
	
	signal(SIGINT,handler); //Asincrono

	do{		
	   printf("\nUnidades de la temperatura: \n Fahrenheit[Letra f/F] \n Celsius[Letra c/C] \n");
	   fflush(stdin);
	   scanf(" %s", &letra);
	}while((letra != 'c') && (letra != 'f') && (letra != 'C') && (letra != 'F'));
		
	sprintf(fpad,"%s","/dev/i2c-1");
	if ((file_i2c = open(fpad, O_RDWR)) < 0)
	{	
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		error = 1;

	}
	
	if(!error){ 
		if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
		{
			printf("Failed to acquire bus access and/or talk to slave.\n");
			//ERROR HANDLING; you can check errno to see what went wrong
			error = 1;
		}
		
		if(!error){	
			while(run){
			
			
				write(file_i2c, NULL, 0);			//Step 1, wakeup
				usleep(1000);

				buf[0]=0x03;				//Get humidity and temperature // para leer registros
				buf[1]=0x00;				//Start address
				buf[2]=0x04;    	        //Number of registers
				write(file_i2c, buf, 3);
				usleep(1500);
		
				read(file_i2c, buf, 6);
		
				humedad_t = ((buf[2] << 8) | buf[3]);
		
				temperatura_t = ((buf[4] << 8) | buf[5]);
			
				if((letra == 'f') || (letra == 'F')){
					temperatura_t = (temperatura_t*9/5) + 32;
				}
		
				printf("Humedad: %d.%d \nTemperatura: %d.%d \n\n", humedad_t/10, humedad_t%10, temperatura_t/10, temperatura_t%10);
			
				sleep(3);
		
			}
		
			close(file_i2c);
			printf("-> Fin de ejecucion de programa\n\n\n");
		}
	}
	
	return 0;

}


printf("%" PRIu64 "\n", sumDistanceSquared[i]); //Para pintar 64 bits sin signo

