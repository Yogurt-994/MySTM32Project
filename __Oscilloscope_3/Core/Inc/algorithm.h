/*
 * algorithm.h
 *
 *  Created on: Jul 5, 2022
 *      Author: 王志涵
 */

#ifndef INC_ALGORITHM_H_
#define INC_ALGORITHM_H_

#include "main.h"
#include "base.h"
#include "arm_math.h"

#define u32 uint32_t
#define u16 uint16_t
#define u8 uint8_t

#define AD_Size 1024
#define AD_Size1 300
#define AD_Size2 1200
#define AD_Size3 3000

/*  正弦参数  */
typedef struct _SinWave_T   //数组参数结构体
{
    float amp;      //峰峰值 mv（阻抗匹配之后）
    float freq;     //频率 Hz
    float phase;     //相位 o
	float period;   //周期 us
}SinWave_T;
extern SinWave_T tSinwave;

/*  波形参数结构体  */
typedef struct _ArrayParam_T   //数组参数结构体
{
    float max;      //最大值
    float min;      //最小值
    float tft_len;  //波形一个周期占多少像素
    float tft_cycle;
    float Vpp;   //峰峰值 mV
    float Period;//周期   us
    float Aver;  //平均值 mv
    float Rms;   //有效值 mv
    float Fre;
    float rmsDivideVpp;
}ArrayParam_T;
extern ArrayParam_T tAD_Params;
extern ArrayParam_T tAD_Params1;
void Calc_array(ArrayParam_T *params,float* calc_addr,u32 calc_len);    //计算数组的参数
void Calc_array1(ArrayParam_T *params,float* calc_addr,u32 calc_len);
int * __sinWaveData(int points,int amplitude,int mid_value,int * _sinWave);

/*  傅里叶变换  */
extern float
TFT_arr1[2][AD_Size1],
*pTFT_arr1, *pTFT_arr_end1,

TFT_arr2[2][AD_Size2],
*pTFT_arr2, *pTFT_arr_end2,

TFT_arr3[2][AD_Size3],
*pTFT_arr3, *pTFT_arr_end3
;


void calc_FFT(float*Input,float*Output);
void PowerPhaseRadians_f32(float32_t *_ptr, float32_t *_phase, uint16_t _usFFTPoints, float32_t _uiCmpValue);
void cal_fftPhase(float*Input,float*Output);

/*  AD采样  */

#define AD_mV_Scale 0.3125f
#define AD_V_Scale 0.0003125f

#define AD_mV_Scale_new 0.3023317334945769f
#define AD_V_Scale_new 0.0003023317334945769f

#define ADS8688_ZERO    32767

#define AD24_mV_Scale 0.0005960464832810452
#define AD24_V_Scale  0.0000005960464832810452

extern float
AD_arr1[2][AD_Size1],
*pAD_arr1,*pAD_arr_end1,		//多通道采样可采用二维数组

AD_arr2[2][AD_Size2],
*pAD_arr2,*pAD_arr_end2,

AD_arr3[2][AD_Size3],
*pAD_arr3,*pAD_arr_end3,

AD_sum_arr[AD_Size],
*pAD_sum_arr,*pAD_sum_arr_end;

void ADarr_Init(void);
//void get_AD_Results(void);


/* 数据决策 */
#define CHOICE_LEN 5
#define THRESHOLD  0.01f
#define ROW     20   //最大支持20路滤波

#define AVER    0   //平均值
#define MANY    1   //众数
#define MID     2   //中位数
#define SMOOTH  3   //平滑输出
#define MAX     4   //最大值
#define MIN     5   //最小值
#define NON     6   //无操作

float many_in_array(float *p);						//计算众数
void Sort(float *a, u8 n);							//排序
float is_Smooth(float* arr,u32 len);				//判断平滑
float Make_Choices(float choice,u16 row,u16 mode);	//多路决策
void quickSort(float *arr, int star, int end);
void swap(float *left, float *right);

/* 贝塞尔函数 */
double bessi0(double x);
double bessi1(double x);
double bessi(int n,double x);


/* FIR滤波 */
//#define FIR_NUM     AD_Size          	//FIR点数
//#define BLOCK_SIZE  128              	//计算单次FIR
//#define FIR_ORDER   64               	//滤波器阶数
//#define FIR_SHIFT   FIR_ORDER/2			//FIR群延时移位
//#define FIR_LEN     FIR_ORDER+1         //滤波器系数个数
//#define NUMBLOCKS   FIR_NUM/BLOCK_SIZE  //需要调用arm_fir_f32的次数
//extern uint16_t FIR_Shift;              //移位阶数的一半|FIR群延时移位
//uint16_t calc_FIR_W(uint32_t Ts,uint32_t Tc);
//void calc_FIR(float *input,uint16_t w);
//void FIR_calc(float *input);
#endif /* INC_ALGORITHM_H_ */
