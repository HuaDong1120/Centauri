/*
 *File: cr_base64.h
 *------------------
 * this file exports functions for encode or decode base64.
 */
#ifndef _cr_base64_h
#define _cr_base64_h
#include <string>

namespace Centauri {
    namespace Base64 {
        /**
         * Function:Base64decode_len
         * Usage: int n = Base64decode_len(buffer)
         * Return size of buffer_code;
         */
        int Base64decode_len(const char* buffer_coded);

        /**
         * Function:Base64decode
         * Usage: int n = Base64decode(starBuf,endBuf)
         * Return decode buffer point and size;
         */
        int Base64decode(char* bufplain, const char* bufcoded);

        /**
         * Function:Base64encode
         * Usage: int n = Base64encode(starBuf,endBuf,size)
         * Return encode buffer point and size;
         */
        int Base64encode(char* encoded, const char* string, int len);

        /**
        * Function:base64_encode
        * Usage: int n = base64_encode(buffer);
        * Return encode buffer;
        */
        std::string base64_encode(const std::string& string_to_encode);

        /**
        * Function:base64_decode
        * Usage: int n = base64_decode(buffer);
        * Return decode buffer;
        */
        std::string base64_decode(const std::string& string_to_decode);

        /**
         * Function:saveStringToFile
         * Usage: int n = saveStringToFile(buffer,"1.jpg");
         * Return true or false;
         */
        bool saveStringToFile(const std::string& binaryString, const std::string& outputFilePath);

        /**
         * Function:saveStringToFile
         * Usage: int n = readFileToString("j.jpg",buffer);
         * Return true or false;
         */
        bool readFileToString(const std::string& filePath, std::string& content);
    }
}
#endif // !_cr_base64_h

