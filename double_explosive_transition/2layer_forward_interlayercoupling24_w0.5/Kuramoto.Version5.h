#ifndef KURAMOTO_VERSION5_H_INCLUDED
#define KURAMOTO_VERSION5_H_INCLUDED
/*****************************************************************************************************************************/
/*** In our simulation, we consider N = 1000. The initial phases of the oscillators are randomly sampled from a uniform    ***/
/*** distribution within the range −π ≤ θiI(II) ≤ π. To obtain the results, we numerically solve the equations described   ***/
/*** in Equation (1) using the fourth-order Runge-Kutta method with a time step of dt = 0.01. The simulation is conducted  ***/
/*** for a total of 40,000 steps. In our simulation, we calculate the average RI(II) over the final 80% of the simulation  ***/
/*** duration, which corresponds to the period when the system has settled into a steady state.                            ***/
/*****************************************************************************************************************************/
/*** Topic: Dynamic Runge-Kutta 4th Order Method application								                               ***/
/***        solved numerically using RungeKutta 4th order method                                                           ***/
/*** Investigating the effect of frequency arrangement of the nodes in the dynamics of two-layer networks                  ***/
/*** Version Release 17.12 rev 11256                                                Ali-Seif                               ***/
/*** Github address:                                            https://github.com/AliSeif96                               ***/
/***                                                            https://github.com/Articles-data/Frequency-Arrangement     ***/
/*** The latest code update: 09/17/2024                                                                                    ***/
/*** Code implemented in Code:Visual Studio Code V 1.93.1                                                                  ***/
/*** MSI: PX60 6QD/ DDR4                                                                                                   ***/
/*** Run under a Intel Core i7-6700HQ CPU @ 2.60GHz  64 based processor with 16 GB RAM                                     ***/
/*****************************************************************************************************************************/
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include<iostream>//for cout                                                                                               $$$$
#include<fstream>//infile /ofstream                                                                                        $$$$
#include <string>//for stod( )                                                                                             $$$$
#include <sstream>//stringstream ss(line)                                                                                  $$$$
#include<ctime>//For Example clock()                                                                                       $$$$
#include <cmath>//For Example pow                                                                                          $$$$
#include <omp.h>//                                                                                                         $$$$
#include <stdio.h>//                                                                                                       $$$$
#define Pi 3.141592653589793238462643383279502884//pi number                                                               $$$$
using namespace std;//                                                                                                     $$$$
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//-----------------------------------------------------------------------------------------------------------------------------
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                          Runge-Kutta 4th                                                $$$$
//                                                          --------------                                                 $$$$
//                                                          \            /                                                 $$$$
//                                                           \          /                                                  $$$$
//                                                            \        /                                                   $$$$
//                                                             \      /                                                    $$$$
//                                                              \    /                                                     $$$$
//                                                               \  /                                                      $$$$
//                                                                \/                                                       $$$$
//-----------------------------------------------------------------------------------------------------------------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
//@@@                                     dydt                                       @@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
double dydt(int specified,int N,double coupling,double W,double L,double B,         //@@@                                   ---
            double a,const double* b,const double* A,double Phase_old_otherlayer,   //@@@                                   ---
            double* Phase_old,double Phase_old_specified)                           //@@@                                   ---
{                                                                                   //@@@                                   ---
    double summation = 0.0;                                                         //@@@                                   ---
    for (int i = 0; i < N; i++){                                                    //@@@                                   ---
        summation += (A[i] * sin((Phase_old[i] - Phase_old_specified + b[i])));     //@@@                                   ---
    }                                                                               //@@@                                   ---
    double connection = 0.0;                                                        //@@@                                   ---
    connection = (L*B*sin(Phase_old_otherlayer-Phase_old_specified+a));             //@@@                                   ---
    double k = 0;                                                                   //@@@      connection calculated        ---
    k = W + ((coupling/(N * 1.0))*summation) + connection;                          //@@@               all sum             ---
    return k;                                                                       //@@@                                   ---
}                                                                                   //@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
//@@@                                CCRK4                                           @@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
void Runge_Kutta_4(int N,double dt,double coupling,const double* W,const double* L, //@@@                                   ---
                   const double* B,const double* a,const double* const* b,          //@@@                                   ---
                   const double* const* A,double* Phase_old,                        //@@@                                   ---
                   double* Phase_old_otherlayer,double* Phase_new)                  //@@@                                   ---
{                                                                                   //@@@                                   ---
    for (int i = 0; i < N; i++)                                                     //@@@                                   ---
        {                                                                           //@@@                                   ---   
            double k1 = dydt(i,N,coupling,W[i],L[i],B[i],a[i],b[i],A[i],            //@@@                                   ---
                            Phase_old_otherlayer[i],Phase_old,Phase_old[i]);        //@@@                                   ---                                                                       //@@@                                   ---
            double k2 = dydt(i,N,coupling,W[i],L[i],B[i],a[i],b[i],A[i],            //@@@                                   ---
                            Phase_old_otherlayer[i],Phase_old,Phase_old[i]+k1*dt/2.0);//@                                   ---
            double k3 = dydt(i,N,coupling,W[i],L[i],B[i],a[i],b[i],A[i],            //@@@                                   ---
                            Phase_old_otherlayer[i],Phase_old,Phase_old[i]+k2*dt/2.0);//@                                   ---
            double k4 = dydt(i,N,coupling,W[i],L[i],B[i],a[i],b[i],A[i],            //@@@                                   ---
                            Phase_old_otherlayer[i],Phase_old,Phase_old[i]+k3*dt);  //@@@                                   ---
            Phase_new[i] = Phase_old[i]+dt/6.0*(k1+2.0*k2+2.0*k3+k4);               //@@@                                   ---
        }                                                                           //@@@                                   ---
}                                                                                   //@@@                                   ---
//-----------------------------------------------------------------------------------------------------------------------------
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                         Order Parameter                                                 $$$$
//                                                          --------------                                                 $$$$
//                                                          \            /                                                 $$$$
//                                                           \          /                                                  $$$$
//                                                            \        /                                                   $$$$
//                                                             \      /                                                    $$$$
//                                                              \    /                                                     $$$$
//                                                               \  /                                                      $$$$
//                                                                \/                                                       $$$$
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
//@@@                                Check scale -pi tp pi                           @@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
void check_scale(int N, double* phi)                                                //@@@                                   ---
{                                                                                   //@@@                                   ---
    for (int i = 0; i < N; i++)                                                     //@@@                                   ---
    {                                                                               //@@@                                   ---
        while(abs(phi[i])>Pi){                                                      //@@@                                   ---
            if (phi[i]>0){                                                          //@@@                                   ---
                phi[i]=phi[i]-2*Pi;                                                 //@@@                                   ---
            }else if(phi[i]<0){                                                     //@@@                                   ---
                phi[i]=phi[i]+2*Pi;                                                 //@@@                                   ---
            }                                                                       //@@@                                   ---
        }                                                                           //@@@                                   ---
    }                                                                               //@@@                                   ---
}                                                                                   //@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
//@@@                                order_parameter                                 @@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
double order_parameter(int N, double* phi)                                          //@@@                                   ---
{                                                                                   //@@@                                   ---
    double rc = 0.0, rs = 0.0;                                                      //@@@                                   ---
    for (int j = 0; j < N; j++)                                                     //@@@                                   ---
    {                                                                               //@@@                                   ---
        rc += cos(phi[j]);                                                          //@@@                                   ---
        rs += sin(phi[j]);                                                          //@@@                                   ---
    }                                                                               //@@@                                   ---
    return sqrt(pow(rc, 2) + pow(rs, 2)) / (1.0 * N);                               //@@@                                   ---
}                                                                                   //@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
//@@@                                  previous phases                               @@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
double* for_loop_equal(double* Phase) {                                             //@@@calculate initial theta            ---
    return Phase;                                                                   //@@@                                   ---
}                                                                                   //@@@                                   ---
//-----------------------------------------------------------------------------------------------------------------------------
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                        read file to arrey                                               $$$$
//                                                          --------------                                                 $$$$
//                                                          \            /                                                 $$$$
//                                                           \          /                                                  $$$$
//                                                            \        /                                                   $$$$
//                                                             \      /                                                    $$$$
//                                                              \    /                                                     $$$$
//                                                               \  /                                                      $$$$
//                                                                \/                                                       $$$$
//-----------------------------------------------------------------------------------------------------------------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
//@@@                               W=Naturalfrequency .txt                          @@@@ Read data from text               ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
double* read_1D_W(string Filename, int Numberofnode)                                //@@@ (Phases & frequency & Matrix)     ---
{                                                                                   //@@@                                   ---
    double* data_1D = new double[Numberofnode];                                     //@@@                                   ---
    ifstream file("./Example/W=Naturalfrequency/" + Filename + ".txt");             //@@@                                   ---
    if (!file)                                                                      //@@@                                   ---
    {                                                                               //@@@                                   ---
        cout << "WARNING! W=Natural frequency file is not here!" << endl;           //@@@                                   ---
    }                                                                               //@@@                                   ---
    else                                                                            //@@@                                   ---
    {                                                                               //@@@                                   ---
        for (int i = 0; i < Numberofnode; i++)                                      //@@@                                   ---
        {                                                                           //@@@                                   ---
            file >> data_1D[i];                                                     //@@@                                   ---
        }                                                                           //@@@                                   ---
        cout << "W of "<<Filename + "\tloaded\t First data=" <<                     //@@@                                   ---
         data_1D[0]<< "\tLastst data="<< data_1D[Numberofnode-1] <<endl;            //@@@                                   ---
    }                                                                               //@@@                                   ---
    file.close();                                                                   //@@@                                   ---
    return data_1D;                                                                 //@@@                                   ---
}                                                                                   //@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
//@@@                               I=InitialPhases .txt                             @@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
double* read_1D_I(string Filename, int Numberofnode)                                //@@@                                   ---
{                                                                                   //@@@                                   ---
    double* data_1D = new double[Numberofnode];                                     //@@@                                   ---
    ifstream file("./Example/I=InitialPhases/" + Filename + ".txt");                //@@@                                   ---
    if (!file)                                                                      //@@@                                   ---
    {                                                                               //@@@                                   ---
        cout << "WARNING! W=Natural frequency file is not here!" << endl;           //@@@                                   ---
    }                                                                               //@@@                                   ---
    else                                                                            //@@@                                   ---
    {                                                                               //@@@                                   ---
        for (int i = 0; i < Numberofnode; i++)                                      //@@@                                   ---
        {                                                                           //@@@                                   ---
            file >> data_1D[i];                                                     //@@@                                   ---
        }                                                                           //@@@                                   ---
        cout << "I of "<<Filename + "\tloaded\t First data=" <<                     //@@@                                   ---
         data_1D[0]<< "\tLastst data="<< data_1D[Numberofnode-1] <<endl;            //@@@                                   ---
    }                                                                               //@@@                                   ---
    file.close();                                                                   //@@@                                   ---
    return data_1D;                                                                 //@@@                                   ---
}                                                                                   //@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
//@@@                       B=Interlayer connection .txt                             @@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
double* read_1D_B(string Filename, int Numberofnode)                                //@@@                                   ---
{                                                                                   //@@@                                   ---
    double* data_1D = new double[Numberofnode];                                     //@@@                                   ---
    ifstream file("./Example/B=Interlayer connection/" + Filename + ".txt");        //@@@                                   ---
    if (!file)                                                                      //@@@                                   ---
    {                                                                               //@@@                                   ---
        cout << "WARNING!\tB=Interlayer connection\t"<<Filename<<                   //@@@                                   ---
        " file is not here!" << endl;                                               //@@@                                   ---
    }                                                                               //@@@                                   ---
    else                                                                            //@@@                                   ---
    {                                                                               //@@@                                   ---
        for (int i = 0; i < Numberofnode; i++)                                      //@@@                                   ---
        {                                                                           //@@@                                   ---
            file >> data_1D[i];                                                     //@@@                                   ---
        }                                                                           //@@@                                   ---
        cout << "B of "<<Filename + "\tloaded\t First data=" <<                     //@@@                                   ---
         data_1D[0]<< "\tLastst data="<< data_1D[Numberofnode-1] <<endl;            //@@@                                   ---
    }                                                                               //@@@                                   ---
    file.close();                                                                   //@@@                                   ---
    return data_1D;                                                                 //@@@                                   ---
}                                                                                   //@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
//@@@                       B=Interlayer connection .txt                             @@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
double* read_1D_a(string Filename, int Numberofnode)                                //@@@                                   ---
{                                                                                   //@@@                                   ---
    double* data_1D = new double[Numberofnode];                                     //@@@                                   ---
    ifstream file("./Example/a=Interlayer frustration/" + Filename + ".txt");       //@@@                                   ---
    if (!file)                                                                      //@@@                                   ---
    {                                                                               //@@@                                   ---
        cout << "WARNING!\ta=Interlayer frustration\t"<<Filename<<                  //@@@                                   ---
        " file is not here!" << endl;                                               //@@@                                   ---
    }                                                                               //@@@                                   ---
    else                                                                            //@@@                                   ---
    {                                                                               //@@@                                   ---
        for (int i = 0; i < Numberofnode; i++)                                      //@@@                                   ---
        {                                                                           //@@@                                   ---
            file >> data_1D[i];                                                     //@@@                                   ---
        }                                                                           //@@@                                   ---
        cout << "a of "<<Filename + "\tloaded\t First data=" <<                     //@@@                                   ---
         data_1D[0]<< "\tLastst data="<< data_1D[Numberofnode-1] <<endl;            //@@@                                   ---
    }                                                                               //@@@                                   ---
    file.close();                                                                   //@@@                                   ---
    return data_1D;                                                                 //@@@                                   ---
}                                                                                   //@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
//@@@                       B=Interlayer connection .txt                             @@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
double* read_1D_L(string Filename, int Numberofnode)                                //@@@                                   ---
{                                                                                   //@@@                                   ---
    double* data_1D = new double[Numberofnode];                                     //@@@                                   ---
    ifstream file("./Example/L=Interlayer coupling/" + Filename + ".txt");          //@@@                                   ---
    if (!file)                                                                      //@@@                                   ---
    {                                                                               //@@@                                   ---
        cout << "WARNING!\tL=Interlayer coupling\t"<<Filename<<                     //@@@                                   ---
        " file is not here!" << endl;                                               //@@@                                   ---
    }                                                                               //@@@                                   ---
    else                                                                            //@@@                                   ---
    {                                                                               //@@@                                   ---
        for (int i = 0; i < Numberofnode; i++)                                      //@@@                                   ---
        {                                                                           //@@@                                   ---
            file >> data_1D[i];                                                     //@@@                                   ---
        }                                                                           //@@@                                   ---
        cout << "L of "<<Filename + "\tloaded\t First data=" <<                     //@@@                                   ---
         data_1D[0]<< "\tLastst data="<< data_1D[Numberofnode-1] <<endl;            //@@@                                   ---
    }                                                                               //@@@                                   ---
    file.close();                                                                   //@@@                                   ---
    return data_1D;                                                                 //@@@                                   ---
}                                                                                   //@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
//@@@                          Read matrix connection                               //@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
double** read_2D_b(string Filename, int Numberofnode)                               //@@@                                   ---
{                                                                                   //@@@                                   ---
    double** data_2D = new double* [Numberofnode];                                  //@@@                                   ---
    for (int i = 0; i < Numberofnode; i++)                                          //@@@                                   ---
        data_2D[i] = new double[Numberofnode];                                      //@@@                                   ---
    ifstream file("./Example/b=Intralayer frustration/" + Filename + ".txt");       //@@@                                   ---
    if (!file)                                                                      //@@@                                   ---
    {                                                                               //@@@                                   ---
        cout << "WARNING!\tb=Intralayer frustration matrix\t"<<Filename<<           //@@@                                   ---
        " file is not here!" << endl;                                               //@@@                                   ---
        return data_2D;                                                             //@@@                                   ---
    }                                                                               //@@@                                   ---
    else                                                                            //@@@                                   ---
    {                                                                               //@@@                                   ---
        for (int i = 0; i < Numberofnode; i++)                                      //@@@                                   ---
        {                                                                           //@@@                                   ---
            for (int j = 0; j < Numberofnode; j++)                                  //@@@                                   ---
            {                                                                       //@@@                                   ---
                double elem = 0;                                                    //@@@                                   ---
                file >> elem;                                                       //@@@                                   ---
                data_2D[i][j] = elem;                                               //@@@                                   ---
            }                                                                       //@@@                                   ---
        }                                                                           //@@@                                   ---
    }                                                                               //@@@                                   ---
            cout << "b of "<<Filename + "\tloaded\t First data=" <<                 //@@@                                   ---
         data_2D[0][1]<< "\tLastst data="<< data_2D[0][Numberofnode-1] <<endl;      //@@@                                   ---
    return data_2D;                                                                 //@@@                                   ---
}                                                                                   //@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
//@@@                          Read matrix connection                               //@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
double** read_2D_A(string Filename, int Numberofnode)                               //@@@                                   ---
{                                                                                   //@@@                                   ---
    double** data_2D = new double* [Numberofnode];                                  //@@@                                   ---
    for (int i = 0; i < Numberofnode; i++)                                          //@@@                                   ---
        data_2D[i] = new double[Numberofnode];                                      //@@@                                   ---
    ifstream file("./Example/A=Intralayeradjacencymatrix/" + Filename + ".txt");    //@@@                                   ---
    if (!file)                                                                      //@@@                                   ---
    {                                                                               //@@@                                   ---
        cout << "WARNING!\tA=Intralayer adjacency matrix\t"<<Filename<<             //@@@                                   ---
        " file is not here!" << endl;                                               //@@@                                   ---
        return data_2D;                                                             //@@@                                   ---
    }                                                                               //@@@                                   ---
    else                                                                            //@@@                                   ---
    {                                                                               //@@@                                   ---
        for (int i = 0; i < Numberofnode; i++)                                      //@@@                                   ---
        {                                                                           //@@@                                   ---
            for (int j = 0; j < Numberofnode; j++)                                  //@@@                                   ---
            {                                                                       //@@@                                   ---
                double elem = 0;                                                    //@@@                                   ---
                file >> elem;                                                       //@@@                                   ---
                data_2D[i][j] = elem;                                               //@@@                                   ---
            }                                                                       //@@@                                   ---
        }                                                                           //@@@                                   ---
    }                                                                               //@@@                                   ---
            cout << "A of "<<Filename + "\tloaded\t First data=" <<                 //@@@                                   ---
         data_2D[0][1]<< "\tLastst data="<< data_2D[0][Numberofnode-1] <<endl;      //@@@                                   ---
    return data_2D;                                                                 //@@@                                   ---
}                                                                                   //@@@                                   ---
//-----------------------------------------------------------------------------------------------------------------------------
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                             data.txt                                                    $$$$
//                                                          --------------                                                 $$$$
//                                                          \            /                                                 $$$$
//                                                           \          /                                                  $$$$
//                                                            \        /                                                   $$$$
//                                                             \      /                                                    $$$$
//                                                              \    /                                                     $$$$
//                                                               \  /                                                      $$$$
//                                                                \/                                                       $$$$
//-----------------------------------------------------------------------------------------------------------------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
//@@@                               count rows file in .txt                         //@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
int count_rows_file(string file1)                                                   //@@@                                   ---
{                                                                                   //@@@                                   ---
    int rows = 0, cols = 0;                                                         //@@@                                   ---
    string line, item;                                                              //@@@                                   ---
    ifstream file(file1);                                                           //@@@                                   ---
    if (!file)                                                                      //@@@                                   ---
    {                                                                               //@@@                                   ---
        cout << "WARNING! Data file is not here!" << endl;                          //@@@                                   ---
    }                                                                               //@@@                                   ---
    else                                                                            //@@@                                   ---
    {                                                                               //@@@                                   --- 
        while (getline(file, line))                                                 //@@@                                   ---
        {                                                                           //@@@                                   ---
            rows++;                                                                 //@@@                                   ---
            if (rows == 1)                                                          //@@@First row only:                    ---
            {                                                                       //@@@determine the number of columns    ---
                stringstream ss(line);                                              //@@@Set up up a stream from this line  ---
                while (ss >> item) cols++;                                          //@@@Each item delineated by spaces     ---
            }                                                                       //@@@adds one to cols                   ---
        }                                                                           //@@@                                   ---
        file.close();                                                               //@@@                                   ---
        cout << "\nFile had " << rows << " rows" << endl;                           //@@@                                   ---
    }                                                                               //@@@                                   ---
    return rows;                                                                    //@@@                                   ---
}                                                                                   //@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
//@@@                               Read Data in .txt                               //@@@                                   ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                   ---
double* read_data(string name_of_file)                                              //@@@                                   ---
{                                                                                   //@@@                                   ---
    int rows=count_rows_file(name_of_file);                                         //@@@                                   ---
    double* data = new double[rows+1];                                              //@@@                                   ---
    string kk;                                                                      //@@@                                   ---
    ifstream fp(name_of_file);                                                      //@@@                                   ---
    if (!fp)                                                                        //@@@                                   ---
    {                                                                               //@@@                                   ---
        cout << "WARNING! Data file is not here!" << endl;                          //@@@                                   ---
    }                                                                               //@@@                                   ---
    else                                                                            //@@@                                   ---
    {                                                                               //@@@                                   ---
       string line, item;                                                           //@@@                                   ---
        for (int i=0;i<rows;i++){                                                   //@@@                                   ---
             fp >> kk;                                                              //@@@                                   ---
            data[i+1] = stod(kk);                                                   //@@@                                   ---
        }                                                                           //@@@                                   ---
        for (int x=1;x<=rows;x++){                                                  //@@@                                   ---
            cout <<"data["<<x<<"]=\t" <<data[x] << endl;                            //@@@                                   ---
        }                                                                           //@@@                                   ---
    }                                                                               //@@@                                   ---
    fp.close();                                                                     //@@@                                   ---
    return data;                                                                    //@@@                                   ---
}                                                                                   //@@@                                   ---
//-----------------------------------------------------------------------------------------------------------------------------
#endif // KURAMOTO_VERSION5_H_INCLUDED
