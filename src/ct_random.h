/*
 *File: cr_random.h
 *------------------
 * this file exports functions for generating pseudorandom numbers.
 */
#ifndef _cr_random_h
#define _cr_random_h

namespace Centauri {
    namespace Random {
        /*
         *Function:randomInteger
         *Usage: int n = randomInteger(low,high)
         *------------------------------------
         *Return a random integer in the range low to high,inclusive.
         */
        int randomInteger(int low, int high);

        /*
         *Function:randomReal
         *Usage: double d = randomReal(low,high)
         *------------------------------------
         *Return a random real number in the half-open interval (low,high).
         * A half-open interval include the first endpoint but not the second,
         * which mean that the result is always greater than or equal to low but
         * strictly less than high.
         */
        double randomReal(double low, double high);

        /*
         *Function:randomChance
         *Usage: if ( randomChance( p ) )....
         *------------------------------------
         *Return true with the probability indicatedby p.
         * The argument p must be a floating-point number between
         * 0 (never) and 1 (always).For example ,calling randomChance(.30)
         * return true 30 precent of time.
         */
        bool randomChance(double p);

        /*
         *Function:setRandomSeed
         *Usage: setRandomSeed(seed)
         *------------------------------------
         *Sets the internal random number seed to the specified value You can
         * use the function to set a specific starting point for pseudorandom
         * sequence or to ensure that program behavior is repeatable during the
         * debugging phase.
         */
        void setRandomSeed(int seed);
    }
}
#endif // !_cr_random_h

