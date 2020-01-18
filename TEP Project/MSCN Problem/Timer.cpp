//
//  Timer.cpp
//  TEP Project
//
//  Created by Michał Raszczuk on 17/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#include "Timer.h"

CTimer::CTimer()
: m_bIsRunning(false) {
    
}

void CTimer::Start() {
    
    clock_gettime(_CLOCK_REALTIME, &m_timeStart);
    m_bIsRunning = true;
}

uint64_t CTimer::Stop() {
    
    clock_gettime(_CLOCK_REALTIME, &m_timeEnd);
    m_timeMid = m_timeEnd;
    m_bIsRunning = false;
    
    return (m_timeEnd.tv_nsec - m_timeStart.tv_nsec);
}

long CTimer::GetSeconds() {
    
    if(m_bIsRunning) {
        clock_gettime(_CLOCK_REALTIME, &m_timeMid);
        
        return (m_timeMid.tv_sec - m_timeStart.tv_sec);
    }
    
    return (m_timeEnd.tv_sec - m_timeStart.tv_sec);
}
