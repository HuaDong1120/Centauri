#include "cr_base64.h"
//init variable
#include <windows.h>
#include <algorithm>
#include  <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
static const unsigned char pr2six[256] =
{
    /* ASCII table */
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
    64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
    64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};

static constexpr  char basis_64[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//init local function
int Centauri::Base64::Base64decode_len(const char* buffer_coded)
{
    int nbytesdecoded;
    const unsigned char* bufin;
    int nprbytes;

    bufin = reinterpret_cast<const unsigned char*>(buffer_coded);
    while(pr2six[*(bufin++)] <= 63);

    nprbytes = (bufin - reinterpret_cast<const unsigned char*>(buffer_coded)) - 1;
    nbytesdecoded = ((nprbytes + 3) / 4) * 3;

    return nbytesdecoded + 1;
}

int Centauri::Base64::Base64decode(char* bufplain, const char* bufcoded)
{
    int nbytesdecoded;
    const unsigned char* bufin;
    unsigned char* bufout;
    int nprbytes;

    bufin = reinterpret_cast<const unsigned char*> (bufcoded);
    while(pr2six[*(bufin++)] <= 63);
    nprbytes = (bufin - reinterpret_cast<const unsigned char*> (bufcoded)) - 1;
    nbytesdecoded = ((nprbytes + 3) / 4) * 3;

    bufout = reinterpret_cast<unsigned char*>(bufplain);
    bufin = reinterpret_cast<const unsigned char*>(bufcoded);

    while(nprbytes > 4) {
        *(bufout++) =
            static_cast<unsigned char>(pr2six[*bufin] << 2 | pr2six[bufin[1]] >> 4);
        *(bufout++) =
            static_cast<unsigned char>(pr2six[bufin[1]] << 4 | pr2six[bufin[2]] >> 2);
        *(bufout++) =
            static_cast<unsigned char>(pr2six[bufin[2]] << 6 | pr2six[bufin[3]]);
        bufin += 4;
        nprbytes -= 4;
    }

    /* Note: (nprbytes == 1) would be an error, so just ingore that case */
    if(nprbytes > 1) {
        *(bufout++) =
            static_cast<unsigned char>(pr2six[*bufin] << 2 | pr2six[bufin[1]] >> 4);
    }
    if(nprbytes > 2) {
        *(bufout++) =
            static_cast<unsigned char>(pr2six[bufin[1]] << 4 | pr2six[bufin[2]] >> 2);
    }
    if(nprbytes > 3) {
        *(bufout++) =
            static_cast<unsigned char>(pr2six[bufin[2]] << 6 | pr2six[bufin[3]]);
    }

    *(bufout++) = '\0';
    nbytesdecoded -= (4 - nprbytes) & 3;
    return nbytesdecoded;
}
int Base64encode_len(int len)
{
    return ((len + 2) / 3 * 4) + 1;
}

int Centauri::Base64::Base64encode(char* encoded, const char* string, int len)
{
    int i;
    char* p = encoded;
    for(i = 0; i < len - 2; i += 3) {
        *p++ = basis_64[(string[i] >> 2) & 0x3F];
        *p++ = basis_64[((string[i] & 0x3) << 4) |
            ((int)(string[i + 1] & 0xF0) >> 4)];
        *p++ = basis_64[((string[i + 1] & 0xF) << 2) |
            ((int)(string[i + 2] & 0xC0) >> 6)];
        *p++ = basis_64[string[i + 2] & 0x3F];
    }
    if(i < len) {
        *p++ = basis_64[(string[i] >> 2) & 0x3F];
        if(i == (len - 1)) {
            *p++ = basis_64[((string[i] & 0x3) << 4)];
            *p++ = '=';
        }
        else {
            *p++ = basis_64[((string[i] & 0x3) << 4) |
                ((int)(string[i + 1] & 0xF0) >> 4)];
            *p++ = basis_64[((string[i + 1] & 0xF) << 2)];
        }
        *p++ = '=';
    }

    *p++ = '\0';
    return static_cast<int>(p - encoded);
}

std::string Centauri::Base64::base64_encode(const std::string& string_to_encode)
{
    try
    {
        const auto src_len = string_to_encode.size();
        int encode_len = Base64encode_len(static_cast<int>(src_len));
        const auto encode_buffer = std::unique_ptr<char[]>(new char[encode_len]);
        encode_len = Base64encode(encode_buffer.get(), string_to_encode.c_str(), src_len);
        return { std::string(encode_buffer.get(), encode_len) };
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return { std::string() };
}

std::string Centauri::Base64::base64_decode(const std::string& string_to_decode)
{
    try
    {
        int decode_len = Base64decode_len(string_to_decode.c_str());
        const std::unique_ptr<char[]> decode_buffer = std::unique_ptr<char[]>(new char[decode_len]);
        decode_len = Base64decode(decode_buffer.get(), string_to_decode.c_str());
        return { std::string(decode_buffer.get(), decode_len) };
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return { std::string() };
}

bool Centauri::Base64::saveStringToFile(const std::string& binaryString, const std::string& outputFilePath)
{
    const std::vector<uint8_t> image(binaryString.begin(), binaryString.end());

    if(std::ofstream outputFile(outputFilePath, std::ios::binary); outputFile.is_open())
    {
        outputFile.write(reinterpret_cast<const char*>(image.data()), image.size());
        outputFile.close();
        return true;
    }
    else
    {
        return false;
    }
}

bool Centauri::Base64::readFileToString(const std::string& filePath, std::string& content)
{
    std::ifstream in(filePath, std::ifstream::binary);
    if(!in.is_open())
    {
        return false;
    }
    std::istreambuf_iterator<char>beg(in), end;
    content.assign(beg, end);
    in.close();
    return true;
}


