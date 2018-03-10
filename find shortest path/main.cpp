//
//  main.cpp
//  find shortest path
//
//  Created by Navroop Singh Bajwa on 08/03/18.
//  Copyright © 2018 Navroop Singh Bajwa. All rights reserved.
//
#include "Header.h"
int main(int argc, const char * argv[]) {
    int r,c;
    cin>>r>>c;
    char inp[100][100];
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cin>>inp[i][j];
        }
    }
    int str,stcol,er,ecol;
    str=stcol=er=ecol=-1;
    cout<<endl;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(inp[i][j]=='s'){
                str=i;stcol=j;
            }
            if(inp[i][j]=='e'){
                er=i;ecol=j;
            }
            cout<<inp[i][j];
        }cout<<endl;
    }
    //s=start
    //o=obstruction
    //e=end
    int bestroute=getbestroute(inp,str,stcol,er,ecol,r,c);
    cout<<bestroute<<endl;
    return 0;
}
