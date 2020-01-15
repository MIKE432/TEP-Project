//
//  Archive.cpp
//  TEP Project
//
//  Created by Michał Raszczuk on 01/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#include "Archive.h"

CArchive::CArchive()
: m_fFile(NULL) {
    
}

bool CArchive::Load(string strFileName) {
    
    if(m_fFile != NULL)
        fclose(m_fFile);
    
    m_fFile = fopen(strFileName.c_str(), "r");
    m_bIsLoadable = true;
    
    return m_fFile!=NULL;
}

bool CArchive::Store(string strFileName) {
    
    if(m_fFile != NULL)
        fclose(m_fFile);
    
    m_fFile = fopen(strFileName.c_str(), "w");
    m_bIsLoadable = false;
    
    return m_fFile!=NULL;
}

bool CArchive::IsValidText(const char* pch) {
       
   while(*pch != '\0') {
       
       if( *pch!=(char)fgetc(m_fFile))
           return false;
       ++pch;
   }
   
   return true;
}

CArchive::~CArchive() {
    
    if(m_fFile != NULL)
        fclose(m_fFile);
}

FILE CArchive::GetFile() {
    
    return *m_fFile;
}

int CArchive::SetFile(string fileName) {
    
    if(m_fFile != NULL)
        return FILE_NOT_CLOSED;
    
    m_fFile = fopen(fileName.c_str(), "a+");
    return NO_ERROR;
}

CArchive& CArchive::operator << ( CArchive& (* fn)(CArchive&) ) {
    
    return fn(*this);
}

CArchive& CArchive::operator << (const char* pchText) {
    
    fwrite(pchText, strlen(pchText), 1, m_fFile);
    
    return *this;
}
CArchive& CArchive::operator << ( char chValue ) {
    
    fprintf(m_fFile, "%c", chValue);
    
    return *this;
}

CArchive& CArchive::operator << (size_t sizeValue) {
    
    fprintf(m_fFile, "%zu", sizeValue);
    
    return *this;
}

//CArchive& CArchive::operator >> (size_t sizeValue) {
//    
//    
//    fscanf(m_fFile, "%zu", sizeValue);
//    return *this;
//}

CArchive& CArchive::operator << ( int nValue ) {
    
    fprintf(m_fFile, "%d", nValue);
    
    return *this;
}

CArchive& CArchive::operator << ( double dValue ) {
    
    fprintf(m_fFile, "%lf", dValue);
    
    return *this;
}

CArchive& CArchive::operator >> ( CArchive& (* fn)(CArchive&) ) {
    
    return fn( *this );
}
CArchive& CArchive::operator >> ( char& chValue ) {

    fscanf(m_fFile, "%c", &chValue);
    
    return *this;
}
CArchive& CArchive::operator >> ( int& nValue ) {

    fscanf(m_fFile,"%d", &nValue);
    
    return *this;
}

CArchive& CArchive::operator >> ( double& dValue ) {

    fscanf(m_fFile,"%lf", &dValue);
    
    return *this;
}
