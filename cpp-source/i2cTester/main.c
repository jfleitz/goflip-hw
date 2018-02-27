#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
 
#define LAMP_DRIVER_ADDRESS        0x04   // I2C
int fd;
 
int main()
{
	int i;
    fd = wiringPiI2CSetup(LAMP_DRIVER_ADDRESS);

    if (fd == -1){
		printf("WiringPi failed\n");
		return;
	}
        
	printf("WiringPi initialized\n");
	
	
//    wiringPiI2CReadReg8 (fd, MPU6050_PWR_MGMT_1);
//    wiringPiI2CWriteReg16(fd, MPU6050_PWR_MGMT_1, 0);
  
    while(1)
    {
		printf("Going to Send 1:65\n");
		getchar();
		wiringPiI2CWriteReg8(fd,1,65);
		
		printf("Going to Send 0:65\n");
		getchar();
		wiringPiI2CWriteReg8(fd,0,65);

		for(i=0;i<65;i++){
			printf("Sent 2:%d\n",i);
			wiringPiI2CWriteReg8(fd,2,i); //slow blink on selected lamp
			
			if(i>0){
				wiringPiI2CWriteReg8(fd,0,i-1); //turn off the prev lamp
			}
			getchar();		
		}

		wiringPiI2CWriteReg8(fd,0,65); //all off
		
		printf("Going to Send 2:65\n");
		getchar();
		wiringPiI2CWriteReg8(fd,2,65);

		printf("Going to Send 3:65\n");
		getchar();
		wiringPiI2CWriteReg8(fd,3,65);

		printf("Going to Send 6:65\n");
		getchar();
		wiringPiI2CWriteReg8(fd,6,65);

				printf("Going to Send 7:65\n");
		getchar();
		wiringPiI2CWriteReg8(fd,7,65);

				printf("Going to Send 8:65\n");
		getchar();
		wiringPiI2CWriteReg8(fd,8,64);

		printf("Going to Send 9:65\n");
		getchar();
		wiringPiI2CWriteReg8(fd,9,65);

		printf("Going to Send 10:65\n");
		getchar();
		wiringPiI2CWriteReg8(fd,10,65);
		
		printf("Going to Send 20:65\n");
		getchar();
		wiringPiI2CWriteReg8(fd,20,65);
		
		printf("Going to Send 30:65\n");
		getchar();
		wiringPiI2CWriteReg8(fd,30,65);
		
		printf("Going to Send 50:65\n");
		getchar();
		wiringPiI2CWriteReg8(fd,50,65);
		
		printf("Going to Send 90:65\n");
		getchar();
		wiringPiI2CWriteReg8(fd,90,65);
		

	}
}