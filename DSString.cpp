#include "DSString.h"
//default dsstring contructor
DSString::DSString(){
    data = new char[1];
    //null
    data[0] = '\0';
    length = 0;
}
//c-string constructor
DSString::DSString(const char *str){
    int i;
    length = setlength(stl);
    data = new char[length + 1];
    data[length] = '\0';
    for(i=0; i < length; 1++){
        data[i] = stl.data[i];
    }
}
