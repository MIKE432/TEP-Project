//
//  main.cpp
//  TEP Project
//
//  Created by Michał Raszczuk on 27/12/2019.
//  Copyright © 2019 Michał Raszczuk. All rights reserved.
//

#include <iostream>
#include "core/Table.h"
#include "core/Matrix.h"
#include "MSCN Problem/MscnProblem.h"
#include "Double.h"
#include "RandomSearch.h"
#include <random>

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    CMscnProblem problem;
    
    CRandom random(10);
    
    problem.Randomize(random);
    
    return 0;
}
