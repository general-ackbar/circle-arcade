
#include "Text.h"


Text::Text(const char *filename, BYTE mode){

    ready = false;
    if( f_open(&myfile, filename,  mode) == FR_OK)
    {
        ready = true;
    }

}

TCHAR* Text::Read()
{
    if(ready)
    {
        UINT btr;
        FSIZE_t len = f_size(&myfile);
        TCHAR* buffer = (TCHAR*)malloc(len);
        f_read(&myfile, buffer, len, &btr);

        //f_gets(buffer, len, &myfile);
        
        return buffer;
    }
    else 
        return 0x0;
}

void Text::Write(CString string)
{
    if(ready)
        f_puts(string, &myfile);

//        UINT btw;
//        f_write(&myfile, (const char*) string, string.GetLength(), &btw);
}

void Text::Append(CString string)
{
    if(ready)
    {
        FSIZE_t len = f_size(&myfile);
        f_lseek(&myfile, len);
        f_puts(string, &myfile);
    }
}

void Text::Close()
{
    f_close(&myfile);  
    ready = false; 
}

Text::~Text()
{
    f_close(&myfile);   
}
