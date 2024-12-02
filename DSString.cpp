#include "DSString.h"
//default dsstring contructor
DSString::DSString(){
    data = new char[1];
    //null
    data[0] = '\0';
    length = 0;
}
// destructor
DSString::~DSString() {
    delete[] data;
}
//c-string constructor
DSString::DSString(const char *str){
    int i;
    length = setlength(str);
    data = new char[length + 1];
    data[length] = '\0';
    for(i=0; i < length; i++){
        data[i] = str.data[i];
    }
}
//copy constructor
DSString::DSString(const DSString &str){
    length = str.length;
    data = new char[length + 1];
    //null terminate
    data[length] = '\0';
    for(int i=0; i<length; i++){
        data[i] = str.data[i];
    }
}