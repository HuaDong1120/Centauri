#ifndef  _ct_signalgenerate_h
#define _ct_signalgenerate_h

namespace Centauri {
    namespace SignamGenerate {
        /**
         * Function:Am
         * Usage:  Centauri::SignamGenerate::Am(result, 100, 1000, 2, 44100, 1, 0.7);
         * Return am time signal;
         */
        void Am(double*result,double freqBaseband,double carrierFrequency,double duration,double samplingRate,double Modulate_Coefficient,double Amplitude);

        /**
         * Function:Fm
         * Usage: Centauri::SignamGenerate::Fm(result_FM, 100, 1000, 2, 44100, 100);
         * Return am time signal;
         */
        void Fm(double* result, double freqBaseband, double carrierFrequency, double duration, double samplingRate, double Frequency_Deviation);
        /**
         * Function:Cw
         * Usage: Centauri::SignamGenerate::Fm(result_FM, 100, 1000, 2, 44100, 100);
         * Return am time signal;
         */
        void Cw(double* result, double freqBaseband,  double duration, double samplingRate);

    }

}


#endif // ! _ct_signalgenerate_h


