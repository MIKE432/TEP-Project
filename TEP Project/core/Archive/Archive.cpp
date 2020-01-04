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

CArchive::CArchive(string fileName, string flags )
: m_fFile(NULL) {
    
    m_fFile = fopen(fileName.c_str(), flags.c_str());
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


int CArchive::Store(string line) {
    
    fprintf(m_fFile, "%s", line.c_str());
    return NO_ERROR;
}

int CArchive::Load() {
    return NO_ERROR;
}

CArchive& CArchive::operator << ( CArchive& (* fn)(CArchive&) ) {
    return fn( *this );
}

CArchive& CArchive::operator << ( char chValue ) {
    
    fprintf(m_fFile, "%c", chValue);
    return *this;
}

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
