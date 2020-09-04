//
//  GA.cpp
//  search
//
//  Created by WU,MENG-TING on 2020/8/16.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//
//  GA vector version

#include "GA.hpp"

GA::GA(){
}

GA::GA(int iter,int pop,double Pm,double Pc,vector<vector<double> > data):iter(iter),pop(pop),Pm(Pm),Pc(Pc),data(data){
    digits = data.size();
    dim = data[0].size();
    vector<double> temp1(digits,0);
    vector<vector<double> > temp2(pop,vector<double>(digits,0));
    vector<double> temp3(pop,0);
    vector<vector<double> > temp4(iter,vector<double>(digits,0));
    vector<double> temp5(iter,0);
    vector<double> temp6(pop,0);
    best_str = temp1;
    Pop_str = temp2;
    Pop_value = temp3;
    Prob = temp3;
    record_str = temp4;
    record_value = temp5;
    for (int i=0;i<pop;i++)
        temp6[i] = i;
    v = temp6;
    random_shuffle(v.begin(),v.end());
}

void GA::Cluster(){
    init_population();
    Cal_Fitness();
    FindBest();
    int it=0;
    while (it<iter&&best_value>0.0){
        vector<vector<double> > newPop (pop,vector<double>(digits,0));
        vector<double> newPop_value(pop,0);
        for (int i=0;i<pop;i+=2){
            vector<vector<double> > parent(2);
            //**********************************//
            // roulette wheel selection
            //**********************************//
            //parent = RouletteWheelSelection();
            //**********************************//
            // tournament selection
            //**********************************//
            parent = TournamentSelection();
            
            vector<vector<double> > children(2);
            if ((double)rand()/(RAND_MAX)<Pc){
                children = Crossover(parent);
            }
            else{
                children = parent;
            }
            if ((double)rand()/(RAND_MAX)<Pm){
                children = Mutation(children);
            }
            newPop[i] = children[0];
            newPop[i+1] = children[1];
        }
        Pop_str = newPop;
        Cal_Fitness();
        UpdateBest();
        record_str[it] = best_str;
        record_value[it] = best_value;
        it++;
    }
}

vector<vector<double> > GA::RouletteWheelSelection(){
    vector<vector<double> > parent(2);
    double base=0.0;
    int n=0;
    double r1,r2;
    do{
        r1 = (double)rand()/(RAND_MAX);
        r2 = (double)rand()/(RAND_MAX);
    }while(r1==r2);
    for (int i=0;i<pop;i++){
        if ( r1>base&&r1<base+Prob[i] ){
            parent[n] = Pop_str[i];
            n++;
        }
        if ( r2>base&&r2<base+Prob[i] ){
            parent[n] = Pop_str[i];
            n++;
        }
        base+=Prob[i];
    }
    return parent;
}

vector<vector<double> > GA::TournamentSelection(){
    vector<vector<double> > parent(2);
    // tournament size
    const int tnt_size = 2;
    for (int i=0;i<2;i++){
        int index[tnt_size];
        random_shuffle(v.begin(),v.end());
        for (int j=0;j<tnt_size;j++){
            index[j] = v[j];
        }
        int bestidx=index[0];
        int best=Pop_value[index[0]];
        for (int i=0;i<tnt_size;i++){
            if (Pop_value[index[i]]<best){
                bestidx = index[i];
                best = Pop_value[index[i]];
            }
        }
        parent[i] = Pop_str[bestidx];
    }
    return parent;
}

vector<vector<double> > GA::Crossover(vector<vector<double> > p){
    vector<vector<double> > parent = p;
    int index = rand()%digits;
    int *temp = new int [digits];
    for (int i=0;i<digits;i++){
        temp[i] = p[0][i];
    }
    for (int i=index+1;i<digits;i++){
        parent[0][i] = p[1][i];
        parent[1][i] = temp[i];
    }
    return parent;
}

vector<vector<double> > GA::Mutation(vector<vector<double> > p){
    vector<vector<double> > parent = p;

    int index1 = rand()%digits;
    int index2 = rand()%digits;
    vector<int> m1(CLUSTER-1,0),m2(CLUSTER-1,0);

    for (int i=0;i<CLUSTER;i++){
        if (i==parent[0][index1])
            continue;
        else if (i>parent[0][index1])
            m1[i-1] = i+1;
        else
            m1[i] = i+1;
    }
    for (int i=0;i<CLUSTER;i++){
        if (i==parent[0][index2])
            continue;
        else if (i>parent[0][index2])
            m2[i-1] = i+1;
        else
            m2[i] = i+1;
    }
    random_shuffle(m1.begin(),m1.end());
    random_shuffle(m2.begin(),m2.end());
    parent[0][index1] = (double)m1[0];
    parent[1][index2] = (double)m2[0];
    return parent;
}

void GA::FindBest(){
    double best=Pop_value[0];
    int bestIdx=0;
    for (int i=0;i<Pop_value.size();i++){
        if (Pop_value[i]<best)
            bestIdx=i;
    }
    best_str = Pop_str[bestIdx];
    best_value = Pop_value[bestIdx];
}

void GA::UpdateBest(){
    double best=Pop_value[0];
    int bestIdx=0;
    for (int i=0;i<Pop_value.size();i++){
        if (Pop_value[i]<best)
            bestIdx=i;
    }
    if (Pop_value[bestIdx]<best_value){
        best_str = Pop_str[bestIdx];
        best_value = Pop_value[bestIdx];
    }
}

void GA::init_population(){
    for (int i=0;i<pop;i++){
        init_point(Pop_str[i]);
    }
}

void GA::init_point(vector<double> &str){
    for (int i=digits-1;i>=0;i--){
        str[i] = rand()%CLUSTER + 1;
    }
}

double GA::total_SSE(vector<double> str,vector<vector<double> > centroids){
    double totalSSE = 0.0;
    for (int i=0;i<str.size();i++){
        for (int j=0;j<data[0].size();j++){
            totalSSE += pow( (data[i][j]-centroids[str[i]-1][j]),2 );
        }
    }
    return totalSSE;
}

void GA::Cal_Fitness(){
    double denomiator=0.0;
    for (int i=0;i<Pop_str.size();i++){
        vector<vector<double> > centroids = Cal_centroids(Pop_str[i]);
        Pop_value[i] = total_SSE(Pop_str[i],centroids);
        denomiator += Pop_value[i];
    }
    // calculate probability for RWS
    for (int i=0;i<Prob.size();i++){
        Prob[i] = Pop_value[i]/denomiator;
    }
}

vector<vector<double> > GA::Cal_centroids(vector<double> str){
    vector<vector<double> > centroids(CLUSTER,vector<double>(dim,0));
    vector<double> count(CLUSTER,0);
    for (int i=0;i<str.size();i++){
        for (int j=0;j<centroids[0].size();j++){
            //1,2,3... -> 0,1,2...
            centroids[str[i]-1][j] += data[i][j];
        }
        count[str[i]-1]++;
    }
    for (int i=0;i<CLUSTER;i++){
        for (int j=0;j<dim;j++){
            centroids[i][j] /= count[i];
        }
    }
    return centroids;
}

