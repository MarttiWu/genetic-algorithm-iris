//
//  GA.hpp
//  search
//
//  Created by WU,MENG-TING on 2020/8/16.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//
//  clustering
//
#ifndef GA_hpp
#define GA_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>

#define CLUSTER 3

using namespace std;

class GA{
public:
    GA();
    GA(int iter,int pop,double Pm,double Pc,vector<vector<double> > data);
    void init_population();
    void init_point(vector<double> &str);
    double total_SSE(vector<double> str,vector<vector<double> > centroids);
    vector<vector<double> > Cal_centroids(vector<double> str);
    void Cal_Fitness();
    double FitnessFunction(vector<double> sol);
    void FindBest();
    void UpdateBest();
    void Cluster();
    vector<double> FitnessFunction();
    vector<vector<double> > RouletteWheelSelection();
    vector<vector<double> > TournamentSelection();
    vector<vector<double> > Crossover(vector<vector<double> > p);
    vector<vector<double> > Mutation(vector<vector<double> > p);
    double get_record_value(int iter){return record_value[iter];}
    vector<double> get_record_str(int iter){return record_str[iter];}
    
private:
    int iter;
    int digits;
    int pop;
    int dim;
    vector<double> best_str; //temp
    double best_value;
    double Pm;
    double Pc;
    vector<vector<double> > Pop_str;
    vector<double> Pop_value;
    vector<double> Prob;//for roulette wheel selection
    vector<vector<double> > data;
    vector<double> v;
    vector<vector<double> > record_str;
    vector<double> record_value;
};

#endif /* GA_hpp */
