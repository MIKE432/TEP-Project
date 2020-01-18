//
//  Timer.hpp
//  TEP Project
//
//  Created by Michał Raszczuk on 17/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#ifndef Timer_h
#define Timer_h

#include <stdio.h>
#include "Optimizer.h"
#include "MscnSolution.h"

class CTimer {
private:
    struct timespec m_timeStart, m_timeEnd, m_timeMid;
    bool m_bIsRunning;
public:
    CTimer();
    
    void Start();
    uint64_t Stop();
    long GetSeconds();
};

#endif /* Timer_hpp */
