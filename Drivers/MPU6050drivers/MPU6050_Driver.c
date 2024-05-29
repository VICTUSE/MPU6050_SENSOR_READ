/*
 * MPU6050_driver.c
 *
 *  Created on: Dec 19, 2023
 *      Author: esmer
 */

#include "MPU6050_driver.h"
#include <stdint.h>

extern I2C_HandleTypeDef hi2c1;


/*
 *
 */
uint16_t MPU6050_SensorTest()
{
	HAL_StatusTypeDef status;

	status = HAL_I2C_IsDeviceReady(&hi2c1,MPU6050_ADDR_GND, 4, 100);

	if(HAL_OK == status)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}
/*
 * Function for Initialization Gyro
 *
 * Let me see if I could build the struct with other initialize function on this one
 */



/*
 * Function for CLK-Sleep and reset configure
 */
uint8_t PWR_CLK_Manage(MPU6050_Handle_t *pMPU6050Handle)
{


	uint8_t tempreg;
	//Clock config
	//Internal 8MHz Clock
    if(pMPU6050Handle->CLK_SRC == Int8MHzOsc)
    {
    	tempreg = 0x00;
    	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_PWR_MGMT_1, 1, &tempreg, 1, 100);
    }
    //External Cloks
    else if(pMPU6050Handle->CLK_SRC == PLL_X)
    {
    	tempreg = 0x1;
       	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_PWR_MGMT_1, 1, &tempreg, 1, 100);
    }
    else if(pMPU6050Handle->CLK_SRC == PLL_Y)
    {
    	tempreg = 0x2;
     	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_PWR_MGMT_1, 1, &tempreg, 1, 100);
    }
    else if(pMPU6050Handle->CLK_SRC == PLL_Z)
    {
    	tempreg = 0x3;
      	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_PWR_MGMT_1, 1, &tempreg, 1, 100);
    }
    else if(pMPU6050Handle->CLK_SRC == PLL_32768)
    {
    	tempreg = 0x4;
       	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_PWR_MGMT_1, 1, &tempreg, 1, 100);
    }
    else if(pMPU6050Handle->CLK_SRC == PLL_192)
    {
     	tempreg = 0x5;
    	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_PWR_MGMT_1, 1, &tempreg, 1, 100);
    }
    else if(pMPU6050Handle->CLK_SRC == Stop_Clk)
    {
    	tempreg = 0x7;
       	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_PWR_MGMT_1, 1, &tempreg, 1, 100);

    }

    //sleep config
    //Stops the clock and keeps the timing generator in reset
    if(pMPU6050Handle->Sleep_Mode == SleepModeOn)
    {
    	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR_GND, REG_PWR_MGMT_1, 1, &tempreg, 1, 100);
    	tempreg |= 0x40;
    	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_PWR_MGMT_1, 1, &tempreg, 1, 100);

    }
    else if(pMPU6050Handle->Sleep_Mode == SleepModeOff)
    {

       	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR_GND, REG_PWR_MGMT_1, 1, &tempreg, 1, 100);
       	tempreg &= 0xBF; //7th bit 1011 1111
       	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_PWR_MGMT_1, 1, &tempreg, 1, 100);

    }

return tempreg;
}
/*
 * Configure frequency output via SampleRate Division register
 */
uint8_t MPU6050_FREQ_CONFİG()
{

	//To manage full frequency (8KHz) SMPRT_DIV=0 output freq = 8KHz
	uint8_t tempreg = 0x07;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_SMPLRT_DIV, 1, &tempreg, 1, 100);

    return tempreg;
}
/*
 * configures the external Frame Synchronization (FSYNC) pin sampling and the Digital Low Pass Filter (DLPF)
 */
uint8_t ExtrnalFrameSYNC()
{
	uint8_t tempreg = 0x00;
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR_GND, REG_CONFIG,1, &tempreg, 1, 100);
	tempreg &= 0xC;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_CONFIG, 1, &tempreg, 1, 100);

	return tempreg;
}
/*
 * FS_SEL selects the full scale range of the gyroscope outputs
 */
uint8_t FS_SEL_Config(MPU6050_Handle_t *pMPU6050Handle)
{

	uint8_t tempreg = 0x00;

	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR_GND, REG_GYRO_CONFIG, 1, &tempreg, 1, 100);
	tempreg = (tempreg & 0xE7) | (pMPU6050Handle->FS_SEL << 3);  //Configure 2 bits at the same operation
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_GYRO_CONFIG, 1, &tempreg, 1, 100);


	return 0;
}

uint8_t AFS_SEL_Config(MPU6050_Handle_t *pMPU6050Handle)
{
	uint8_t tempreg = 0x00;

	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR_GND, REG_ACCEL_CONFIG, 1, &tempreg, 1, 100);
	tempreg = (tempreg & 0xE7) | (pMPU6050Handle->AFS_SEL << 3);  //Configure 2 bits at the same operation
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_ACCEL_CONFIG, 1, &tempreg, 1, 100);

	return 0;
}

/*
 * The accelerometer and gyroscope are filtered according to the value of DLPF_CFG
 */
uint8_t DLFP_Config(MPU6050_Handle_t *pMPU6050Handle)
{
	//external Frame Synchronization (FSYNC) pin sampling config Input disabled
	uint8_t tempreg = 0x00;
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR_GND, REG_CONFIG, 1, &tempreg, 1, 100);
	tempreg = (tempreg & 0xC7) | (0 << 3);  //Configure 3 bits at the same operation
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_CONFIG, 1, &tempreg, 1, 100);

	//The accelerometer and gyroscope are filtered according to the value of DLPF_CFG
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR_GND, REG_CONFIG, 1, &tempreg, 1, 100);
	tempreg = (tempreg & 0xF8);   //Configure 3 bits at the same operation
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_GND, REG_CONFIG, 1, &tempreg, 1, 100);

	return 0;
}


uint16_t Read_Data_16(uint8_t regAdd, uint8_t *pData, uint8_t size)
{

	HAL_StatusTypeDef status;



	status = HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR_GND, regAdd, 1, pData, size, 100);

	 if(HAL_OK != status)
	 {
		 return 0;
	 }
	 else
	 {
		 return 1;
	 }
}

uint8_t Read_Data_8(uint8_t regAdd)
{
	HAL_StatusTypeDef status;
	uint8_t data;

	status = HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR_GND, regAdd, 1, &data, 1, 100);

	if(HAL_OK != status )
	{
		return 0;
	}
	else
	{
		return data;
	}

}

int16_t TEMP_DEGREE()
{

	uint8_t pTempData[2];
	int16_t Tempraw;
	int16_t TempDegree;

	Read_Data_16(REG_TEMP_OUT_H, pTempData, 2);

	Tempraw = ((pTempData[0] <<8) | pTempData[1]);
    TempDegree = (Tempraw/340) +36.53;

    return TempDegree;
}

/*
GyroCal GYRO_CALIB()
{

	/*
    * Take the mean of 2000 values in a raw to decrease deviations (only purpose of this for loop is finding a calibration value)
    */
	//initiliaze gyro specific variables
/*	uint8_t GyroData[6]; //3-axis data buffer address
  	int16_t GyroRaw[3];  //axis raw values

    GyroCal gyroCal;


  	int i;
  	for(i=0; i<2000; i++)
  	{

  	  prevtime2 = time2;
  	  time2 = HAL_GetTick();
  	  elapsedtime2 = (time2 - prevtime2)*1000;

    	Read_Data_16(REG_GYRO_XOUT_H, GyroData, 6);  //Read all axis values in a row

        GyroRaw[0] = (GyroData[0] << 8 | GyroData[1]);  //2 byte gyro X axis raw value
        GyroRaw[1] = (GyroData[2] << 8 | GyroData[3]);  //2 byte gyro Y axis raw value
        GyroRaw[2] = (GyroData[4] << 8 | GyroData[5]);  //2 byte gyro Z axis raw value

        gyroCal.GyroCalX += GyroRaw[0];  //sum all the samples in a variable
        gyroCal.GyroCalY += GyroRaw[1];
        gyroCal.GyroCalZ += GyroRaw[2];

     HAL_Delay(3);
	  	}

  	gyroCal.GyroCalX /= 2000; //take the mean of the all samples
  	gyroCal.GyroCalY /= 2000;
  	gyroCal.GyroCalZ /= 2000;

  	return gyroCal;
}
*/

GyroValues GYRO_DEGREE(MPU6050_Handle_t *pMPU6050Handle)
{

    uint8_t GyroData[6]; //3-axis data buffer address
  	int16_t GyroRaw[3];  //axis raw values

    GyroValues gyroValues; //Declared a struct to hold gyro values

	Read_Data_16(REG_GYRO_XOUT_H, GyroData, 6);  //Read all axis values in a row

	GyroRaw[0] = (GyroData[0] << 8 | GyroData[1]);  //2 byte gyro X axis raw value
    GyroRaw[1] = (GyroData[2] << 8 | GyroData[3]);  //2 byte gyro Y axis raw value
    GyroRaw[2] = (GyroData[4] << 8 | GyroData[5]);  //2 byte gyro Z axis raw value

	/*
     * Calculate Degree/second values according to FS_SEL
     */
    if(pMPU6050Handle->FS_SEL == FS_250degree)  //In case of Full Scale Range is 250 degree
    {

    	gyroValues.GyroX =  (GyroRaw[0] / 131.0);    //To find actual values divide GyroRaw's with LSB Sensitivity/degree according to Full scale range
    	gyroValues.GyroY =  (GyroRaw[1] / 131.0) ;
    	gyroValues.GyroZ =  (GyroRaw[2] / 131.0) ;
    }
    else if(pMPU6050Handle->FS_SEL == FS_500degree) //In case of Full Scale Range is 500degree
    {

    	gyroValues.GyroX =  (GyroRaw[0] / 65.5);  //To find actual values divide GyroRaw's with LSB Sensitivity/degree according to Full scale range
    	gyroValues.GyroY =  (GyroRaw[1] / 65.5);
    	gyroValues.GyroZ =  (GyroRaw[2] / 65.5);
    }
    else if(pMPU6050Handle->FS_SEL == FS_1000degree) //In case of Full Scale Range is 1000 degree
    {

    	gyroValues.GyroX =  (GyroRaw[0] / 32.8);  //To find actual values divide GyroRaw's with LSB Sensitivity/degree according to Full scale range
    	gyroValues.GyroY =  (GyroRaw[1] / 32.8);
    	gyroValues.GyroZ =  (GyroRaw[2] / 32.8);
    }
    else if(pMPU6050Handle->FS_SEL == FS_2000degree) //In case of Full Scale Range is 2000 degree
    {


    	gyroValues.GyroX =  (GyroRaw[0] / 16.4);  //To find actual values divide GyroRaw's with LSB Sensitivity/degree according to Full scale range
    	gyroValues.GyroY =  (GyroRaw[1] / 16.4);
    	gyroValues.GyroZ =  (GyroRaw[2] / 16.4);
    }


return gyroValues; //return the struct with gyro values
}

ACCValues ACC_DEGREE(MPU6050_Handle_t *pMPU6050Handle)
{

	uint8_t AccData[6]; //3-axis data buffer address
 	int16_t AccRaw[3];  //axis acc raw values

 	ACCValues accValues; //Declared a struct to hold acc values

 	Read_Data_16(REG_ACCEL_XOUT_H, AccData, 6);

 	AccRaw[0] = (AccData[0] << 8 | AccData[1]);  //2 byte ACC X axis raw value
    AccRaw[1] = (AccData[2] << 8 | AccData[3]);  //2 byte ACC Y axis raw value
    AccRaw[2] = (AccData[4] << 8 | AccData[5]);  //2 byte ACC Z axis raw value

 	/*
    * Calculate Degree/second values according to FS_SEL
     */
    if(pMPU6050Handle->AFS_SEL == AFS_2G)
    {

    	accValues.ACCX =  (AccRaw[0] / 16384.0);    //To find actual values divide ACCRAW's with LSB Sensitivity/g according to ACC Full scale range
    	accValues.ACCY =  (AccRaw[1] / 16384.0) ;
    	accValues.ACCZ =  (AccRaw[2] / 16384.0) ;
    }
    else if(pMPU6050Handle->AFS_SEL == AFS_4G)
    {

    	accValues.ACCX =  (AccRaw[0] / 8192.0);    //To find actual values divide ACCRAW's with LSB Sensitivity/g according to ACC Full scale range
     	accValues.ACCY =  (AccRaw[1] / 8192.0) ;
    	accValues.ACCZ =  (AccRaw[2] / 8192.0) ;
 	    }
     else if(pMPU6050Handle->AFS_SEL == AFS_8G)
     {

    	accValues.ACCX =  (AccRaw[0] / 4096.0);    //To find actual values divide ACCRAW's with LSB Sensitivity/g according to ACC Full scale range
       	accValues.ACCY =  (AccRaw[1] / 4096.0) ;
      	accValues.ACCZ =  (AccRaw[2] / 4096.0) ;
     }
     else if(pMPU6050Handle->AFS_SEL == AFS_16G)
     {
    	 accValues.ACCX =  (AccRaw[0] / 2048.0);    //To find actual values divide ACCRAW's with LSB Sensitivity/g according to ACC Full scale range
         accValues.ACCY =  (AccRaw[1] / 2048.0) ;
    	 accValues.ACCZ =  (AccRaw[2] / 2048.0) ;
     }

    return accValues;
}

