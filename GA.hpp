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
//#include <memory.h>
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
    /*
    int Sum(int *str);
    int get_max(){return Max;}
    int find_best_index();
     */
    ////////
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
    //int Max;
    //vector<vector<double> > centroid;
    //vector<double> centroid_value;
    
    vector<double> best_str; //temp
    double best_value;
    double Pm;
    double Pc;
    vector<vector<double> > Pop_str;
    vector<double> Pop_value;
    vector<double> Prob;//for roulette wheel selection
    //int *f;
    vector<vector<double> > data;
    //int tnt_count;
    vector<double> v;
    vector<vector<double> > record_str;
    vector<double> record_value;
    //static int count;
};
//int count=0;

#endif /* GA_hpp */
