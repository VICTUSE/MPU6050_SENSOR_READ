/*
 * MPU6050_driver.h
 *
 *  Created on: Dec 19, 2023
 *      Author: esmer
 */

#ifndef MPU6050_DRIVER_H_
#define MPU6050_DRIVER_H_

#include "stm32f0xx_hal.h"




/*
 * Macros for MPU6050
 */
#define MPU6050_ADDR_GND (0x68 << 1 )
#define MPU6050_ADDR_VCC (0x69 << 1 )

#define REG_SELF_TEST_X  0x0D
#define REG_SELF_TEST_Y  0x0E
#define REG_SELF_TEST_Z  0x0F
#define REG_SELF_TEST_A  0x10

#define REG_SMPLRT_DIV   0x19

#define REG_CONFIG       0x1A

#define REG_GYRO_CONFIG  0x1B

#define REG_ACCEL_CONFIG 0x1C

#define REG_ACCEL_XOUT_H 0x3B
#define REG_ACCEL_XOUT_L 0x3C

#define REG_ACCEL_YOUT_H 0x3D
#define REG_ACCEL_YOUT_L 0x3E

#define REG_ACCEL_ZOUT_H 0x3F
#define REG_ACCEL_ZOUT_L 0x40

#define REG_TEMP_OUT_H   0x41
#define REG_TEMP_OUT_L   0x42

#define REG_GYRO_XOUT_H  0x43
#define REG_GYRO_XOUT_L  0x44

#define REG_GYRO_YOUT_H  0x45
#define REG_GYRO_YOUT_L  0x46

#define REG_GYRO_ZOUT_H  0x47
#define REG_GYRO_ZOUT_L  0x48

#define REG_PWR_MGMT_1   0x6B
#define REG_PWR_MGMT_2   0x6C

/*
 * Configuration macros
 *
 */
#define FS_250degree   0
#define FS_500degree   1
#define FS_1000degree  2
#define FS_2000degree  3

#define AFS_2G   0
#define AFS_4G   1
#define AFS_8G   2
#define AFS_16G  3

#define SleepModeOn   1
#define SleepModeOff  0

#define Int8MHzOsc 0
#define PLL_X      1
#define PLL_Y      2
#define PLL_Z      3
#define PLL_32768  4
#define PLL_192    5
#define Stop_Clk   7

#define WakeFreqLow    0
#define WakeFreq5Hz    1
#define WakeFreq20Hz   2
#define WakeFreq40Hz   3


/*
 * FS_SEL selects the full scale range of the gyroscope outputs
 */


/*
 * AFS_SEL selects the full scale range of the accelerometer outputs
 */


/*
 * Sleep_Mode allows user to select sleep mode on or off
 */


/*
 * CLK_SRC allows user to select clock source or stop it
 */


/*
 * Wake_Cntrl allows user to control the wake up frequency in cycle mode
 */


/*
 * Handle Struct
 */
typedef struct
{
uint8_t FS_SEL;
uint8_t AFS_SEL;
uint8_t Sleep_Mode;
uint8_t CLK_SRC;
uint8_t SMPRT_DIV;

}MPU6050_Handle_t;
/*
 * Structer to return more than one value for GYRO_DEGREE function
 */
typedef struct {
	float GyroX;
	float GyroY;
	float GyroZ;
}GyroValues;

typedef struct{
  	int16_t GyroCalX;  //mean error value
  	int16_t GyroCalY;
  	int16_t GyroCalZ;
}GyroCal;

typedef struct {
	float ACCX;
	float ACCY;
	float ACCZ;
}ACCValues;



/*
 * Function definitions which will be used must be at the end of the header file like this.
 */
uint16_t MPU6050_SensorTest();
uint16_t Read_Data_16(uint8_t regAdd, uint8_t *pData, uint8_t size);
uint8_t Read_Data_8(uint8_t regAdd);
uint8_t PWR_CLK_Manage(MPU6050_Handle_t *);
uint8_t MPU6050_FREQ_CONFİG();
uint8_t ExtrnalFrameSYNC();
uint8_t AFS_SEL_Config(MPU6050_Handle_t *pMPU6050Handle);
uint8_t FS_SEL_Config(MPU6050_Handle_t *pMPU6050Handle);
uint8_t DLFP_Config(MPU6050_Handle_t *pMPU6050Handle);
int16_t TEMP_DEGREE();
GyroValues GYRO_DEGREE(MPU6050_Handle_t *pMPU6050Handle);
ACCValues ACC_DEGREE(MPU6050_Handle_t *pMPU6050Handle);
GyroCal GYRO_CALIB();
#endif /* MPU6050_DRIVER_H_ */

