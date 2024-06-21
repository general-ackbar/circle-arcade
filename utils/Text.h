
#ifndef Text_h
#define Text_h
#pragma once

#include <fatfs/ff.h>
#include <circle/util.h>
#include <circle/string.h>
#include <circle/alloc.h>




class Text{


    
private:
    FIL myfile;
    bool ready;

public:	
    ~Text();
    Text(const char* filename, BYTE mode = FA_READ);  
    TCHAR* Read();
    void Write(CString string);
    void Append(CString string);
    void Close();


};

#endif 
