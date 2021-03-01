//============================================================================
// Author      : Wiktor Jurek
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <stdio.h>
#include <bits/stdc++.h>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cstdio>
#include <ctime>
using namespace std;


void show(int *tab, int n)
{
    fstream file;
    file.open("out.txt", ios::out | ios::app);
    if(file.good() == true)
    {
        for(int i=0; i<n; i++)
        {
            file<<tab[i]<<" ";
            cout<<tab[i]<<" ";
        }
        file<<"\n";
        cout<<endl;
        file.close();
    }
}





int main()
{

    int chose,n,N,t;
    t=1;
    cout<<"Problem spelnialnosci formul boolowskich"<<endl;
    cout<<"Wybierz algorytm :"<<endl<<"[1] - WALKSAT"<<endl<<"[2] = GSAT"<<endl;
    cin>>chose;

    cout<<"Wprowadz ilosc zmiennych (max 8, numeracja od 0 do n-1)"<<endl<<"n= ";
    cin>>n;


    //inicjalizacjha i uzpoe³nienie tablicy zmiennych 0 lub 1
    int *xTab = new int[n];
    srand (time(NULL));
    for(int i=0; i<n; i++)
    {
        xTab[i] = rand() % 2;
        cout<<xTab[i]<<" ";
    }
    cout<<endl;
    if(chose ==2)
    {
        cout<<"Podaj dlugosc listy tabu (minimum 1 max "<<n-1<<")"<<endl<<"t= ";
        cin>>t;
    }

    cout<<"Podaj ilosc implicentow"<<endl<<"N= ";
    cin>>N;
    //inicjalizacjia tablicy przechowuj¹cej implicenty
    int **tab = new int* [N];
    for(int i=0; i<N; i++)
    {
        tab[i] = new int[n];
        for(int j=0; j<n; j++)
        {
            tab[i][j] = 0;
        }
    }
    //wczytanie implicentów i zamiana ich z postaci string na tablicê
    cout<<"Wprwadz kolejne implicenty w nowych liniach:"<<endl;
    for(int i=0; i<N; i++)
    {
        string implicent;
        int plusCount;
        plusCount = 0;
        cin>> implicent;
        for(int j=0; j<(int)implicent.length(); j++)
        {
            if(implicent[j] == '+')
            {
                plusCount +=1;
            }
        }
        plusCount +=1;
        string *tempImpli = new string[plusCount];
        for(int j=0; j<plusCount; j++)
        {
            tempImpli[j] = "";
        }
        int index;
        index =0;
        for(int j=0; j<(int)implicent.length(); j++)
        {
            if(implicent[j] != '+')
            {
                tempImpli[index] += implicent[j];
            }
            else
            {
                index+=1;
            }
        }
        for(int j=0; j<plusCount; j++)
        {
            //	cout<<tempImpli[j][(int)tempImpli[j].length()-1]<<endl;
            int iN;
            iN = (int)tempImpli[j][(int)tempImpli[j].length()-1] -48;
            if(tempImpli[j][0] =='!')
            {
                tab[i][iN] = -1;
            }
            else
            {
                tab[i][iN] = 1;
            }
        }
    }

    int* impliVal = new int[N];
    int counter;
    counter =1;
    for(int i=0; i<n; i++)
    {
        counter = counter *2;
    }

    counter = n*n ;

    //algorytm WALKSAT
    clock_t start, stop;
    double czas;
    start = clock();
    if(chose == 1)
    {
        bool success =false;
        while(counter>0)
        {
            //sprawdzamy wartoœæ logiczn¹ ka¿dego kolejnego implicentu i zapisujemy do tablicy
            for(int i=0; i<N; i++)
            {
                bool findOne;
                findOne = false;

                for(int j=0; j<n; j++)
                {

                    if(tab[i][j] == -1)
                    {
                        if(xTab[j] == 0)
                        {
                            findOne = true;
                        }
                    }
                    if(tab[i][j] == 1)
                    {
                        if(xTab[j] == 1)
                        {
                            findOne = true;
                        }
                    }

                }
                if(findOne == true)
                {
                    impliVal[i] = 1;
                }
                else
                {
                    impliVal[i] = 0;
                }
            }
            //sprawdzamy czy wszystkie implicenty s¹ równe 1
            bool finish = true;
            int zeroImpliCounter =0;
            for(int i=0; i<N; i++)
            {
                if(impliVal[i] == 0)
                {
                    finish = false;
                    zeroImpliCounter +=1;
                }
            }
            //jezeli tak wtedy zakoñcz i wyœwietl wynik
            if(finish == true)
            {
                cout<<"Znaleziono rozwiazanie"<<endl;
                for(int i =0; i<n; i++)
                {
                    cout<<"x"<<i<<" ="<<xTab[i]<<endl;
                }
                counter =0;
                success = true;
                //je¿eli nie wylosuj dowlony zerowy implicent, nastêpnie wylosuj zmienn¹ i zaneguj j¹
            }
            else
            {
                int tempImpli, ix, impliIndex, tempCounter;
                tempCounter=1;
                tempImpli = rand() % zeroImpliCounter +1;

                for(int i=0; i<N; i++)
                {
                    if(impliVal[i] == 0 && tempImpli == tempCounter)
                    {
                        impliIndex =i;
                    }
                    else if(impliVal[i] ==0 && tempImpli != tempCounter)
                    {
                        tempCounter +=1;
                    }
                    else
                    {
                    }
                }
                bool isX;
                isX = false;

                while(isX == false)
                {
                    ix = rand() % n;
                    if(tab[impliIndex][ix] != 0)
                    {
                        if(xTab[ix] == 0)
                        {
                            xTab[ix] =1;
                        }
                        else
                        {
                            xTab[ix] =0;
                        }
                        isX =true;
                    }

                }
                counter-=1;
            }
        }
        if(success == false)
        {
            cout<<"Nie znaleziono rozwizania !";
        }


    }
//algorytm GSAT
    else
    {
        bool success;
        success = false;
        int *tabu = new int[t];
        for(int i=0; i<t; i++)
        {
            tabu[i] = n;
        }
        while(counter>0)
        {

            for(int i=0; i<N; i++)
            {
                bool findOne;
                findOne = false;

                for(int j=0; j<n; j++)
                {

                    if(tab[i][j] == -1)
                    {
                        if(xTab[j] == 0)
                        {
                            findOne = true;
                        }
                    }
                    if(tab[i][j] == 1)
                    {
                        if(xTab[j] == 1)
                        {
                            findOne = true;
                        }
                    }

                }
                if(findOne == true)
                {
                    impliVal[i] = 1;
                }
                else
                {
                    impliVal[i] = 0;
                }

            }
            //sprawdzamy czy wszystkie implicenty s¹ równe 1
            bool finish = true;
            int zeroImpliCounter =0;
            for(int i=0; i<N; i++)
            {
                if(impliVal[i] == 0)
                {
                    finish = false;
                    zeroImpliCounter +=1;
                }
            }
            //je¿eli tak wtedy zakoñcz i wyœwietl wynik
            if(finish == true)
            {
                cout<<"Znaleziono rozwiazanie"<<endl;
                for(int i =0; i<n; i++)
                {
                    cout<<"x"<<i<<" ="<<xTab[i]<<endl;
                }
                counter =0;
                success = true;
                //je¿eli nie wylosuj dowlony zerowy implicent, nastêpnie wylosuj zmienn¹ i zaneguj j¹
            }
            else
            {
                int amount, chIndex;
                amount = N;
                chIndex = n;
                for(int i =0; i<n; i++)
                {
                    bool isTabu = false;

                    for(int j=0; j<t; j++)
                    {
                        if(i == tabu[j])
                        {
                            isTabu = true;
                        }
                    };
                    if(isTabu ==false)
                    {
                        if(xTab[i] == 0)
                        {
                            xTab[i] = 1;
                        }
                        else
                        {
                            xTab[i] =0;
                        }
                        for(int k=0; k<N; k++)
                        {
                            bool findOne;
                            findOne = false;

                            for(int l=0; l<n; l++)
                            {

                                if(tab[k][l] == -1)
                                {
                                    if(xTab[l] == 0)
                                    {
                                        findOne = true;
                                    }
                                }
                                if(tab[k][l] == 1)
                                {
                                    if(xTab[l] == 1)
                                    {
                                        findOne = true;
                                    }
                                }

                            }
                            if(findOne == true)
                            {
                                impliVal[k] = 1;
                            }
                            else
                            {
                                impliVal[k] = 0;
                            }
                        }
                        int zCounter =0;
                        for(int k=0; k<N; k++)
                        {
                            if(impliVal[k] == 0)
                            {

                                zCounter +=1;
                            }
                        }
                        if(amount > zCounter)
                        {
                            amount = zCounter;
                            chIndex =i;
                        }
                        if(xTab[i] == 0)
                        {
                            xTab[i] =1;
                        }
                        else
                        {
                            xTab[i] = 0;
                        }
                    }
                }
                if(xTab[chIndex] ==0 )
                {
                    xTab[chIndex] =1;
                }
                else
                {
                    xTab[chIndex] =0;
                }
                for(int j=t-1; j>=0; j--)
                {
                    if(j>0)
                    {
                        tabu[j] = tabu[j-1];
                    }
                    else
                    {
                        tabu[0] = chIndex;
                    }

                }
                counter-=1;
                if(amount ==0)
                {
                    cout<<"Znaleziono rozwiazanie"<<endl;
                    for(int i =0; i<n; i++)
                    {
                        cout<<"x"<<i<<" ="<<xTab[i]<<endl;
                    }
                    counter =0;
                    success = true;
                }

            }



        }
        if(success == false)
        {

            cout<<"Nie znaleziono rozwizania !";

        }
    }
    stop = clock();

    cout<<endl<<"Czas wykonania algorytmu :"<<(double)(stop-start)/1000<<"s"<<endl;






    return 0;
}

