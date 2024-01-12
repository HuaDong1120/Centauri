#include "ct_signalGenerate.h"
#include <cmath>
#include <iostream>
const double PI = 3.14159265358979323846;
void Centauri::SignamGenerate::Am(double* result, double freqBaseband, double carrierFrequency, double duration, double samplingRate, double Modulate_Coefficient, double Amplitude)
{
    //采样的点数，为采样时间除以采样间隔，相当于乘采样率
    double N_poit = duration * samplingRate;
    double t = 0;
    double carrierSignal = 0;
    double modulationSignal = 0;
    for(int i = 1; i <= N_poit; i++)
    {
        //采样时间序列点
        t = i / N_poit;
        //载波信号
        carrierSignal = std::cos(2 * PI * carrierFrequency * t);
        //调制信号
        modulationSignal = Amplitude * (1 + Modulate_Coefficient * std::cos(2 * PI * freqBaseband * t))* carrierSignal;
        
        result[i] = modulationSignal;

    }

}

void Centauri::SignamGenerate::Fm(double* result, double freqBaseband, double carrierFrequency, double duration, double samplingRate, double Frequency_Deviation)
{
    double N_poit = duration * samplingRate;
    double t = 0;
    double modulationSignal = 0;
    for(int i = 1; i <= N_poit; i++)
    {
        //采样时间序列点
        t = i / N_poit;
        //调制信号
        modulationSignal = std::cos(2 * PI * carrierFrequency * t + Frequency_Deviation * std::sin(2 * PI * freqBaseband * t));

        result[i] = modulationSignal;

    }

}

void Centauri::SignamGenerate::Cw(double* result, double freqBaseband, double duration, double samplingRate)
{
    double N_poit = duration * samplingRate;
    double t = 0;
    double modulationSignal = 0;
    for(int i = 0; i < N_poit; i++)
    {
        //采样时间序列点
        t = i / N_poit;
        //调制信号
        modulationSignal = std::cos(2 * PI * freqBaseband * t);

        result[i] = modulationSignal;

    }
}
