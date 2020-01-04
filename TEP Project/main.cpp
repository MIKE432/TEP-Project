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
    
    CMscnProblem problem;

    {
        CRandom random(1);
        problem.Randomize(random);

        CArchive archive;
        archive.Store("testfile2.txt");
        archive << problem;
    }
    {
        CArchive archive;
        archive.Load("testfile2.txt");
        archive >> problem;
    }
    {
        CArchive archive;
        archive.Store("testfile3.txt");
        archive << problem;
    }
    return 0;
}
