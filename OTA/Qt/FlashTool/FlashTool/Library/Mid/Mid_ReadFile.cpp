#include "Library/Mid/Mid_ReadFile.h"

//#define USER_APP "D:\\data\\code\\share with the community\\OTA\\template_thread\\template_thread\\user_app.bin"

QString bin_file;
QFile File_bin;

void Mid_ProcessSetFile(QString file_name)
{
    bin_file = file_name;
}
//This function opens the file, calculates and returns total length in bytes
uint32_t Mid_ProcessFileCalcLen(void)
{
    uint32_t fileLen;

    QFile myFile(bin_file);
    myFile.open(QFile::ReadWrite);

    fileLen = myFile.size();

    myFile.close();

    return fileLen;
}
//This function opens the file , global file handle is used to store the file pointer
void Mid_ProcessFileOpen(void)
 {
    File_bin.setFileName(bin_file);
    File_bin.open(QFile::ReadWrite);
 }
//This function reads the file for a given "len" bytes
uint32_t Mid_ProcessFileRead(uint8_t *buffer, uint32_t len)
{
    File_bin.read((char *)buffer, len);
    return 0;
}

//close the global file handle
void Mid_ProcessFileClose(void)
{
    File_bin.close();
}
uint8_t Mid_ExWordtoByte(uint32_t addr, uint8_t index)
{
      uint8_t value = (addr >> ( 8 * ( index -1)) & 0x000000FF );
      return value;

}

