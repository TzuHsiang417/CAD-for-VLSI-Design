#ifndef _PARAMETER_H
#define _PARAMETER_H

#define K               7       //Wong Liu Algorithm裡的參數K
#define RATIO           0.85    //Wong Liu Algorithm裡溫度T變化的比例
#define FROZEN_RATIO    0.1     //Wong Liu Algorithm裡，當溫度低於某值時，比例降低快速冷卻
#define SEED            3       //srand(SEED)
#define EPSILON         0.001   //Wong Liu Algorithm裡的參數epsilon
#define M3_TRY          100     //限定M3執行的次數
#define MIN_ASPECT      0.5     
#define MAX_ASPECT      2
#define LARGER_ASPECT1  1.75
#define SMALLER_ASPECT1 0.57
#define LARGER_ASPECT2  1.5
#define SMALLER_ASPECT2 0.67
#define LARGER_ASPECT3  1.25
#define SMALLER_ASPECT3 0.8
#define TIME_LIMIT      3500    //程式執行的時間限制

#endif