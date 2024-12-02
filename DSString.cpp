#include "DSString.h"
//deafult constructor
DSString::DSString(){
    data = new char[1];
    //null
    data[0] = '\0';
    len = 0;
}
//c string constructor
DSString::DSString(const char *source){
    len = strlen(source);
    data = new char[len + 1];
    std::strcpy(data, source);
}
//copy constructor
DSString::DSString(const DSString &other){
    len = other.len;              
    data = new char[len + 1];
    std::strcpy(data, other.data);
}
//copy operator
DSString &DSString::operator=(const DSString &other){
    if(this != &other){
        //free memory
        delete[] data;
        len = other.len;
        data = new char[len + 1];
        std::strcpy(data, other.data);
    }
    return *this;
}
//destructor
DSString::~DSString(){
    delete[] data;
}
//this method returns length of string
size_t DSString::length() const{
    return len;
}
//access of char by index
char &DSString::operator[](size_t index){
    return data[index];
}
//two DSStrings
DSString DSString::operator+(const DSString &other) const{
    size_t newLen = len + other.len;
    //memory
    char *combined = new char[newLen + 1];
    std::strcpy(combined, data);
    std::strcat(combined, other.data);
    DSString result(combined);
    //free memory
    delete[] combined;
    return result;
}
//compare DSStrings
bool DSString::operator==(const DSString &other) const{
    return len == other.len && std::strcmp(data, other.data) == 0;
}
//compares two DSStrings
bool DSString::operator<(const DSString &other) const{
    return std::strcmp(data, other.data) < 0;
}
//extracts a substring
DSString DSString::substring(size_t start, size_t numChars) const{
    char *subData = new char[numChars + 1];
    std::strncpy(subData, data + start, numChars);
    //null
    subData[numChars] = '\0';
    DSString subString(subData);
    //free memory;
    delete[] subData;
    return subString;
}
//converts DSString to lowercase
DSString DSString::toLower() const{
    //memory
    char *lowerData = new char[len + 1];
    for(size_t i = 0; i < len; i++){
        lowerData[i] = std::tolower(data[i]);
    }
    //null
    lowerData[len] = '\0';
    DSString lowerString(lowerData);
    //free memory
    delete[] lowerData;
    return lowerString;
}
//return c style string
const char *DSString::c_str() const{
    return data;
}
//overload
std::ostream &operator<<(std::ostream &out, const DSString &str){
    out << str.data;
    return out;
}
