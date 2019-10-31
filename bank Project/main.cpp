//
//  main.cpp
//  project1
//
//  Created by LeOOON on 3/17/18.
//  Copyright © 2018 LeOOON. All rights reserved.
//

#include <iostream>
#include "account.h"
#include <vector>


int main() {
    
    
    cout<<"Bank Account Project RUID: 172009147 Name: Lieyang Chen";
    
    int input = 0;
    account list[9000];
    int listsize=0;
    int refarray[9000];
    for (int i=0;i<=8999;i++){
        refarray[i]=i+1000;
    }
    
    
    while (input!=9){
        menu(&input);
        
        switch (input) {
            case 1:
            makeAccount(list,listsize,refarray);
            listsize++;
            break;
            case 2:
            depositAccount(list,listsize);
            break;
            case 3:
            withdrawAccount(list,listsize);
            break;
            case 4:
            transfer(list,listsize);
            break;
            case 5:
            printAccount(list,listsize);
            break;
            case 6:
            ActiveDeactive(list,listsize);
            break;
            case 7:
            deleteAccount(list,listsize,refarray);
            listsize--;
            break;
            case 8:
            PrintAllAcount(list,listsize);
            break;
            case 9:
            break;
            default:
            cout<<"No such a selection.";
            break;
        }
        
        
    }
    return 0;
    
}

