//
//  account.hpp
//  project1
//
//  Created by LeOOON on 3/17/18.
//  Copyright © 2018 LeOOON. All rights reserved.
//

#ifndef account_hpp
#define account_hpp
#include <stdio.h>
# include <iostream>
#include <string>
using namespace std;

struct account{
    unsigned int accountnumber;
    string firstname;
    string lastname;
    double balance;
    bool status;
    int indexofrefarray;
};

double validinput();
void menu(int*);
void makeAccount(account[],int,int[]);
void printAccount(account list[],int size);
void transfer(account list[],int size);
void PrintAllAcount(account list[],int size);
void depositAccount(account list[],int size);
void ActiveDeactive(account list[],int size);
void withdrawAccount(account list[],int size);
void sortAcounts(account list[],int size); // sort the accounts using the account numbers
void deleteAccount(account[],int,int[]);
void swap(account[],int,int);

#endif /* account_hpp */

