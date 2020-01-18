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
#include "DiffEvol.h"
#include "Optimizer.h"
#include "Problem.h"
#include "Timer.h"
#include <random>

using namespace std;

int main(int argc, const char * argv[]) {
    
    CTimer timer;
    timer.Start();
    
    CRandom random;

    {
//        problem.GenerateInstance(200);
//
//        CArchive archive;
//        archive.Store("testfile2.txt");
//        archive << problem;
    }
    
    CMscnProblem problem;
    {

        CArchive archive;
        archive.Load("testfile.txt");
        archive >> problem;


    }
    
    cout << "middle seconds: " << timer.GetSeconds() << endl;
    CRandomSearch randomSearch(&problem);
    {
        CArchive archive;
        randomSearch.GenerateSolution(random);
        double* solution = new double[3];
        solution[0] = 1;
        solution[1] = 1;
        solution[2] = 1;
        CDiffEvol diffEvol = CDiffEvol(&problem, &randomSearch, 200);

        CSolution* pSolution = diffEvol.GetSolution(random);
        int error;


        cout << problem.GetQuality(pSolution->GetBeginPtr(), problem.GetSolutionSize(), error);
        if(pSolution != NULL) {

            CArchive archive;
            archive.Store("testSolution11.txt");

            archive << *pSolution;

            delete pSolution;
        }
    }
    
    timer.Stop();
    cout << "end seconds: " << timer.GetSeconds() << endl;
    
    return 0;
}
