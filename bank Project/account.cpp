//
//  account.cpp
//  project1
//
//  Created by LeOOON on 3/17/18.
//  Copyright © 2018 LeOOON. All rights reserved.
//

#include "account.h"
#include <random>
#include <ctime>
#include <typeinfo>

void menu(int *num) { int select = 0;
    cout<<endl<<endl<<endl;
    cout << "Welcome! Select options below:" << endl;
    cout << "\t1. Make new account."
    << "\n\t2. Deposit to an account." << "\n\t3. Withdraw from an account."<< "\n\t4. Transfer money."
    << "\n\t5. Print account." << "\n\t6. Activate/Deactivate an account."<< "\n\t7. Delete an account." << "\n\t8. Display all accounts."
    << "\n\t9. Quit." << endl;
    cout << "Selection:\t";
    select=validinput();
    *num = select;
    cout<<endl<<endl;
}



double validinput(){
    double x;
    cin>>x;
    while (x<0||(cin.fail()==1)){
        cout<<"\nInvalid Input."<<endl;
        cin.clear();
        cin.ignore(256,'\n');
        cout<<"Enter a new one: ";
        cin>>x;// There might be a special case that when user enter a value which starts with a digit and has characters in somewhere of the remaining part (ie. 77e8s),the validinput may not be able to detect the error. This is because cin would take the number 77 as the input for the current value and it is valid, and the following cin would take character 'e' as input. Therefore, the invalid input is not detected at the first time. This would make the output on the console look weird and may cause some serious problem if you enter some value like this.
    }
    cin.clear();
    cin.ignore(256,'\n');//These two instruction is for preventing the outcome of the above-mentioned case.
    return x;
    }




void makeAccount(account list[],int size,int refarray[]){
    default_random_engine engine{static_cast<unsigned int>(time(0))};
    uniform_int_distribution<unsigned int> randomnum{0, 8999};
    
    int x=randomnum(engine);// randomly generate an index between 0-8999
    
    while (refarray[x]==0){ //recall that the passead refarray contains elements from 1000-9999, so refarray's element won't be zero unless it has already been used by another object
        x=randomnum(engine); // if so, re-generate an index and check if its corresponding element is 0; if not, it means that this index's element has not been used yet, then end loop and use this index's element to initialize the new object's accountnumber
    }
    
    list[size].accountnumber=refarray[x];
    list[size].status=1;//activate account when creating it.
    list[size].indexofrefarray=x;
    refarray[x]=0; // after taking the accountnumber from refarray through the randomly generated index, the corresponding element has to be assigned by 0 so that it won't be assigned to another new object
    cout<<"Creating bank account number "<<list[size].accountnumber<<endl<<endl;
    
    cout<<"Enter first name: ";
    cin>>list[size].firstname;
    cout<<"Enter last name: ";
    cin>>list[size].lastname;
    cout<<"Enter starting balance: ";
    list[size].balance=validinput();
}

void depositAccount(account list[],int size){
    cout<<"Enter account number for deposit: ";
    int accountnum;
    accountnum=validinput();
    cout<<"Enter amount to be deposit: ";
    double amount;
    amount=validinput();
    int indicator{-1};
    
    for (int i=0;i<=size-1;i++){
        if (accountnum==list[i].accountnumber){
            indicator=0;
            if (list[i].status==1){
                list[i].balance+=amount;
                break;
            }
            else {
                cout<<endl<<">> Account is not active. Process cannot be done! First, you need to activate this account.";
                break;
            }
        }
    }
    if (indicator==-1){
        cout<<"Account number not found."<<endl;
        depositAccount(list,size);
    }
    
}

void withdrawAccount(account list[],int size){
    cout<<"Enter account number for withdraw: ";
    int accountnum;
    accountnum=validinput();
    cout<<"Enter amount to be withdraw: ";
    double amount;
    amount=validinput();
    int indicator{-1};
    
    for (int i=0;i<=size-1;i++){
        if (accountnum==list[i].accountnumber){
            indicator=0;
            if (list[i].status==1){
                list[i].balance-=amount;
                break;
            }
            else {
                cout<<endl<<">> Account is not active. Process cannot be done! First, you need to activate this account.";
                break;
            }
        }
    }
    if (indicator==-1){
        cout<<"Account number not found."<<endl;
        withdrawAccount(list,size);
    }
}


void transfer(account list[],int size){
    if (size==1){
        cout<<"Only one account left, Transfer is not allowed."<<endl;
        return;
    }
    else{
        
        
        cout<<"Enter account number for the sender: ";
        int accountnum1;
        accountnum1=validinput();
        cout<<"Enter account number for the receiver: ";
        int accountnum2;
        accountnum2=validinput();
        cout<<"Enter amount to transfer: ";
        double amount;
        amount=validinput();
        int index1{-2};
        int index2{-2};
        int indicator1{-1};
        int indicator2{-1};
        
        
        
        
        
        
        for (int i=0;i<=size-1;i++){
            if (accountnum1==list[i].accountnumber){
                indicator1=0;
                index1=i;
                if (list[i].status==1){
                    list[i].balance-=amount;
                    break;
                }
                else {
                    cout<<endl<<">> Account is not active. Process cannot be done! First, you need to activate this account.";
                    index1=-1;
                    break;
                }
            }
        }
        
        
        for (int i=0;i<=size-1;i++){
            if (accountnum2==list[i].accountnumber){
                indicator2=0;
                if (list[i].status==1||index1!=-1){
                    list[i].balance+=amount;
                    index2=i;
                    break;
                }
                else if (list[i].status==1||index1==-1){
                    break;
                }
                else if (list[i].status==0||index1!=-1){
                    list[index1].balance+=amount;
                    cout<<endl<<">> Account is not active. Process cannot be done! First, you need to activate this account.";
                    break;
                }
            }
        }
        if (indicator2==-1||indicator1==-1){
            cout<<"Account(s) number(s) not found."<<endl;
            if (indicator1==-1&&indicator2==-1){
                transfer(list,size);
                
            }
            else if (indicator1!=-1){
                list[index1].balance+=amount;
                transfer(list,size);
            }
            else if (indicator2!=-1){
                list[index2].balance-=amount;
                transfer(list,size);
            }
            
            
        }
        
    }
}


void printAccount(account list[],int size){
    
    cout<<"Enter account number to print: ";
    int accountnum;
    accountnum=validinput();
    int indicator{-1};
    
    for (int i=0;i<=size-1;i++){
        if (accountnum==list[i].accountnumber){
            indicator=0;
            if (list[i].status==1){
                cout<<"Account number: "<<list[i].accountnumber<<endl<<"Balance: "
                <<list[i].balance<<endl<<"Last Name: "<<list[i].lastname<<endl<<"First Name: "
                <<list[i].firstname;
                break;
            }
            else {
                cout<<endl<<">> Account is not active. Process cannot be done! First, you need to activate this account.";
                break;
            }
        }
    }
    if (indicator==-1){
        cout<<"Account number not found."<<endl;
        printAccount(list,size);
    }
}



void ActiveDeactive(account list[],int size){
    cout<<"Enter account number for activation/deactivation: ";
    int accountnum;
    accountnum=validinput();
    cout<<"Press 1 to activate, 0 to deactivate: ";
    bool status;
    cin>>status;
    int indicator{-1};
    for (int i=0;i<=size-1;i++){
        if (accountnum==list[i].accountnumber){
            indicator=0;
            list[i].status=status;
            break;
        }
    }
    if (indicator==-1){
        cout<<"Account number not found."<<endl;
        ActiveDeactive(list,size);
    }
}



void deleteAccount(account list[],int size,int refarray[]){
    cout<<"Enter account number to be deleted: "<<endl;
    int index{-1};
    int accountnum;
    accountnum=validinput();
    int indicator{-1};
    for (int i=0;i<=size-1;i++){
        if (accountnum==list[i].accountnumber){
            indicator=0;
            if (list[i].status==1){
                index=i;
                refarray[list[i].indexofrefarray]=accountnum;// put the deleted accountnum back to refarray
                if (index==size-1){
                    
                }
                else {
                    for (int i=index;i<size-1;i++){
                        list[i]=list[i+1];
                    }
                }
                break;
            }
            else {
                cout<<endl<<">> Account is not active. Process cannot be done! First, you need to activate this account.";
                break;
            }
        }
    }
    if (indicator==-1){
        cout<<"Account number not found."<<endl;
        deleteAccount(list,size,refarray);
    }
    
}

void PrintAllAcount(account list[],int size){
    sortAcounts(list,size);
    for (int i=0;i<=size-1;i++){
        cout<<"Account number: "<<list[i].accountnumber<<"     "<<"Balance: "
        <<list[i].balance<<endl<<"     Last name: "<<list[i].lastname<<"     "
        <<"First name: "<<list[i].firstname<<endl<<endl;
    }
    
    
}


void sortAcounts(account list[],int size){
    
    for (int i{0};i<size;i++){
        int smallest=list[i].accountnumber;
        int smallindex=i;
        for (int j=i+1;j<size;j++){
            if (list[j].accountnumber<smallest){
                smallest=list[j].accountnumber;
                smallindex=j;
            }
        }
        swap(list,smallindex,i);
    }
    
}

void swap(account list[],int newindex, int oldindex){
    account x=list[newindex];
    list[newindex]=list[oldindex];
    list[oldindex]=x;
}

