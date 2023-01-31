#ifndef _BIQUAD_H_
#define _BIQUAD_H_

#include "main.h"
#include <math.h>


biquad* bq_new(int filter_type, float frequency, float Q, float dbGain, int sample_rate);

float bq_process(biquad* bq, float input);

void bq_destroy(biquad* bq);

void bq_print_info(biquad* bq);

void bq_load_coefficients(biquad* bq, int filter_type, float A, float omega, float sn, float cs, float alpha, float beta);

void bq_update_bq_load_coefficients(biquad* bq, int filter_type, float frequency, float Q, float dbGain, int sample_rate);

#endif // _BIQUAD_H_
