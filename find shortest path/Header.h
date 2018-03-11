//
//  Header.h
//  find shortest path
//
//  Created by Navroop Singh Bajwa on 08/03/18.
//  Copyright © 2018 Navroop Singh Bajwa. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include<iostream>
#include <vector>
#include<stack>
#include<algorithm>
#include<string>
using namespace std;

struct path {
    int r,c;
    path(int rr,int cc){
        r=rr;
        c=cc;
    }
};

struct ways{
    bool up,down,right,left;
    ways(bool up,bool down,bool right,bool left){
        this->up=up;
        this->down=down;
        this->right=right;
        this->left=left;
    };
};

struct routeinfo{
    vector<path> currentroute; //path info
    int crtr,crtcol;// current r and c
    int lastway;// last way or can be seen simply by cureentroute.begin()
    int steps;// no of steps
    routeinfo(vector<path> p,int law,int stp,int ct,int crtcl){ //intializer
        currentroute.swap(p);
        lastway=law;
        steps=stp;
        crtr=ct;
        crtcol=crtcl;
    };
};

ways *get_available_paths(char inp[][100],int str,int stcol,int lastway,int r,int c){
    /*
     up=0
     down=1
     left=2
     right=3
     */
    bool up,down,left,right;
    up=down=left=right=false;
    if(str+1<r){
        if(inp[str+1][stcol]=='.'||inp[str+1][stcol]=='e') down=true;
    }
    if(str-1>=0){
        if(inp[str-1][stcol]=='.'||inp[str-1][stcol]=='e') up=true;
    }
    if(stcol+1<c){
        if(inp[str][stcol+1]=='.'||inp[str][stcol+1]=='e') right=true;
    }
    if(stcol-1>=0){
        if(inp[str][stcol-1]=='.'||inp[str][stcol-1]=='e') left=true;
    }
    ways *t=new ways(up,down,right,left);
    return t;
}

/*
 4 node tree will be formed in recursion which will result in max 3 nodes and in worst case 0
 with 0 it will lock value if it had reached its on destination
 else it will just go to next node in next recursion
 */

bool not_visited_path(vector<path> route,int str, int stcol){
    for(auto it=route.begin();it!=route.end();it++){
        if(it->r==str&&it->c==stcol){
            return false;
        }
    }
    return true;
}

void show_the_route_to_user(char inp[][100],vector<path> p,int r,int c,int ec,int erow){
    int output[r][c];
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            output[i][j]=-1;
            if(inp[i][j]=='b')output[i][j]=-2;
        }
    }
    int counter=0;
    for(auto it=p.begin();it!=p.end();it++){
        int rr,cc;
        rr=it->r;
        cc=it->c;
        if(counter==0){
            output[rr][cc]=-3;
            counter++;
        }else{
            output[rr][cc]=counter;
            counter++;
        }
    }
    output[erow][ec]=-4;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(output[i][j]>=0)
                cout<<output[i][j]<<"\t";
            else{
                if(output[i][j]==-1)cout<<".\t";
                if(output[i][j]==-3)cout<<"s\t";
                if(output[i][j]==-2)cout<<"b\t";
                if(output[i][j]==-4)cout<<"e\t";
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

void whilestackisnotempty(char inp[][100],int er,int ecol,int r,int c,stack <routeinfo> differentapproches,vector<int> &count){
    while(!differentapproches.empty()){
        struct routeinfo *t=&differentapproches.top();
        if(t->crtcol==ecol&&t->crtr==er){
            show_the_route_to_user(inp,t->currentroute,r,c,ecol,er);
            count.push_back(t->steps);
            differentapproches.pop();
        }else{
            int lastway=t->lastway;
            vector<path> currentpath=t->currentroute;
            struct path *pathcoverd=new path(t->crtr,t->crtcol);
            currentpath.push_back(*pathcoverd);
            int steps=t->steps;
            int str=t->crtr;
            int stcol=t->crtcol;
            differentapproches.pop();
            struct ways *noofpossibleroute=get_available_paths(inp, str, stcol,lastway, r, c);
            
                if(noofpossibleroute->up==true&&not_visited_path(currentpath,str-1,stcol)){
                    vector<path> for1(currentpath);
                        struct routeinfo *t=new routeinfo(for1,1,steps+1,str-1,stcol);
                        differentapproches.push(*t);
                }
                else if(noofpossibleroute->down==true&&not_visited_path(currentpath,str+1,stcol)){
                    vector<path> for1(currentpath);
                        struct routeinfo *t=new routeinfo(for1,0,steps+1,str+1,stcol);
                        differentapproches.push(*t);
                }
                if(noofpossibleroute->left==true&&not_visited_path(currentpath,str,stcol-1)){
                    vector<path> for1(currentpath);
                        struct routeinfo *t=new routeinfo(for1,3,steps+1,str,stcol-1);
                        differentapproches.push(*t);
                }
                if(noofpossibleroute->right==true&&not_visited_path(currentpath,str,stcol+1)){
                    vector<path> for1(currentpath);
                        struct routeinfo *t=new routeinfo(for1,2,steps+1,str,stcol+1);
                        differentapproches.push(*t);
                }
                
            
        }
        
    }
}

stack <routeinfo> get_stack_initial(stack <routeinfo> &stackinitial,char inp[][100],int str,int stcol,int r,int c){
    struct ways *tt=get_available_paths(inp, str, stcol, -1, r, c);
    vector<path> p;
    struct path *pp=new path(str,stcol);
    p.push_back(*pp);
    
    bool up=tt->up,down=tt->down,right=tt->right,left=tt->left; //can use priority for efficient algo
    
    if(up==true){
        struct routeinfo *t=new routeinfo(p,1,1,str-1,stcol); //since last path will be start //2 ==not down
        stackinitial.push(*t);
    }
    if(down==true){
        struct routeinfo *t=new routeinfo(p,0,1,str+1,stcol); //since last path will be start //1 ==not up
        stackinitial.push(*t);
    }
    if(left==true){
        struct routeinfo *t=new routeinfo(p,3,1,str,stcol-1); //since last path will be start //3 ==not left
        stackinitial.push(*t);
    }
    if(right==true){
        struct routeinfo *t=new routeinfo(p,2,1,str,stcol+1); //since last path will be start //1 ==not right
        stackinitial.push(*t);
    }
    return stackinitial;
    
    
}

int getbestroute(char inp[][100],int str,int stcol,int er,int ecol,int r,int c){
    vector<int> count;
    vector<path> route;
    stack <routeinfo> differentapproches;
    get_stack_initial(differentapproches,inp, str, stcol, r, c);
    whilestackisnotempty(inp, er, ecol, r, c,differentapproches,count);
    auto ret=min_element(count.begin(),count.end());
    cout<<"Size"<<count.size()<<endl;
    cout<<"Steps array : ";
    for(auto it=count.begin();it!=count.end();it++){
        cout<<*it<<" ";
    }cout<<endl;
    if(ret!=count.end()) return *ret;
    return -1;
}

#endif /* Header_h */
