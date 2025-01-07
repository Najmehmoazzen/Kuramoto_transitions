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
#include"Kuramoto.Version5.h"//import Internal library Kuramoto                                                            $$$$
#include <time.h>//import External library for calculate time                                                              $$$$
#include <iomanip>//                                                                                                       $$$$
//-------------------------------------------------------------------------------------------------------------------------$$$$
//                                                              |    |                                                     $$$$
//                                                              |    |                                                     $$$$
//                                                               main                                                      $$$$
//                                                          --------------                                                 $$$$
//                                                          \            /                                                 $$$$
//                                                           \          /                                                  $$$$
//                                                            \        /                                                   $$$$
//                                                             \      /                                                    $$$$
//                                                              \    /                                                     $$$$
//                                                               \  /                                                      $$$$
//                                                                \/                                                       $$$$
//                                           T1=W1+k/N*sum(A1*sin(I1+b1))+L12*B1*sin(I2+a1)                                $$$$
//-----------------------------------------------------------------------------------------------------------------------------
int main(){                                                                     //@@@           Beginning main              ---
    //-------------------------------------------------------------------------------------------------------------------------
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    Read and definition data,          ---
    //@@@                                     data.txt and Example file          @@@@    Number_of_node,Phases_initial,     ---
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    frequency,adj,coupling,delay,time  ---
    const double* data=read_data("data.txt");                                   //@@@ read data from data.txt and write them---
    const int Number_of_node = int(data[1]);                                    //@@@        N=Number_of_node=1000          ---
    cout << "|------------------------------------------------------|\n"<< endl;//@@@                                       ---
    const double* frequency_layer1 = read_1D_W("0.0Layer1",Number_of_node);     //@@@        w=natural frequency      L1    ---
    const double* frequency_layer2 = read_1D_W("0.8Layer2",Number_of_node);     //@@@        w=natural frequency      L2    ---
    double* Phases_initial_layer1 = read_1D_I("origin1",Number_of_node);        //@@@        I=initial Phases         L1    ---
    double* Phases_initial_layer2 = read_1D_I("origin2",Number_of_node);        //@@@        I=initial Phases         L2    ---
    const double* const* adj_layer1 = read_2D_A("Layer1",Number_of_node);       //@@@        A=adjacency matrix       L1    ---
    const double* const* adj_layer2 = read_2D_A("Layer2",Number_of_node);       //@@@        A=adjacency matrix       L2    ---
    const double* bdj_layer1 = read_1D_B("Layer1to2",Number_of_node);           //@@@        B=Interlayer connection  L1    ---
    const double* bdj_layer2 = read_1D_B("Layer2to1",Number_of_node);           //@@@        B=Interlayer connection  L2    ---
    const double* frust_layer1 = read_1D_a("Layer1to2",Number_of_node);         //@@@        a=Interlayer frustration L1    ---
    const double* frust_layer2 = read_1D_a("Layer2to1",Number_of_node);         //@@@        a=Interlayer frustration L2    ---
    const double* const* Intrafrust_layer1 = read_2D_b("Layer1",Number_of_node);//@@@        b=Intralayer frustration L1    ---
    const double* const* Intrafrust_layer2 = read_2D_b("Layer2",Number_of_node);//@@@        b=Intralayer frustration L2    ---
    const double* inter_layer1 = read_1D_L("Layer1to2",Number_of_node);         //@@@        L=Interlayer coupling    L1    ---
    const double* inter_layer2 = read_1D_L("Layer2to1",Number_of_node);         //@@@        L=Interlayer coupling    L2    ---
    cout << "|------------------------------------------------------|\n"<< endl;//@@@                                       ---
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                       ---
    //@@@                                definitions                             @@@@                                       ---
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                       ---
    const int time_stationary = int(data[4] * 0.2);                             //@@@    example T=20 time_stationary= 10   ---
    const int Number_Steps_time_stationary = int(time_stationary / data[3]);    //@@@   for example T=20 dt=0.01 >> = 1000  ---
    int coupling_step = round(data[5]/data[6]);                                 //@@@                                       ---
    ofstream Average_Syncrony(                                                  //@@@                                       ---
        "Save/Average_Syncrony(couplig_SyncL1_SyncL2_Extime)/output.txt");      //@@@       Create Sync file                ---
    double* Phases_next_layer1 = new double[Number_of_node];                    //@@@    Definition Phases next             ---
    double* Phases_next_layer2 = new double[Number_of_node];                    //@@@                                       ---
    double* Phases_layer1_previous = for_loop_equal(Phases_initial_layer1);     //@@@               Phases changer          ---
    double* Phases_layer2_previous = for_loop_equal(Phases_initial_layer2);     //@@@               [node][delay]           ---
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    //@@@                                      coupling loop                    //@@@                                       ---@
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                       ---@
    for (coupling_step;coupling_step <= int(data[7]/data[6]);coupling_step++){  //@@@                                       ---@
        double coupling=coupling_step*data[6];                                  //@@@            call coupling              ---@
        time_t start = time(NULL);                                              //@@@         reset time to zero            ---@
        ostringstream ostrcoupling;                                             //@@@    declaring output string stream     ---@
        ostrcoupling << fixed << setprecision(2) << coupling;                   //@@@  Sending a number as a stream output  ---@
        string strcoupling = ostrcoupling.str();                                //@@@ the str() converts number into string ---@
        ofstream Phases_layer2("Save/Phases(time)VS(Node)/L2_k="+               //@@@       create file for phases L2       ---@
                               strcoupling+"layer2.txt");                       //@@@                                       ---@
        ofstream Phases_layer1("Save/Phases(time)VS(Node)/L1_k="+               //@@@       create file for phases L1       ---@
                               strcoupling+"layer1.txt");                       //@@@                                       ---@
        double Total_syncrony_layer1 = 0;                                       //@@@          def tot synchroney L1        ---@
        double Total_syncrony_layer2 = 0;                                       //@@@          def tot synchroney L2        ---@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@                                        time loop                  //@@@                                       ---@  @
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                       ---@  @
        ofstream time_syncroney("Save/Syncrony(time_SyncL1_SyncL2)/k="+         //@@@                                       ---@  @
                                strcoupling+".txt");                            //@@@                                       ---@  @
        double time_step = double(data[2]);                                     //@@@     reset time for new time           ---@  @        
        for (time_step;time_step < int(data[4]/data[3]);time_step++){           //@@@                                       ---@  @
            double time_loop=time_step*data[3];                                 //@@@                                       ---@  @
            Runge_Kutta_4(Number_of_node,                                       //@@@   Runge-Kutta 4th Order Method  L1    ---@  @
                        data[3],                                                //@@@                                       ---@  @
                        coupling,                                               //@@@                                       ---@  @
                        frequency_layer1,                                       //@@@                                       ---@  @
                        inter_layer1,                                           //@@@                                       ---@  @
                        bdj_layer1,                                             //@@@                                       ---@  @
                        frust_layer1,                                           //@@@                                       ---@  @
                        Intrafrust_layer1,                                      //@@@                                       ---@  @
                        adj_layer1,                                             //@@@                                       ---@  @
                        Phases_layer1_previous,                                 //@@@                                       ---@  @
                        Phases_layer2_previous,                                 //@@@                                       ---@  @
                        Phases_next_layer1);                                    //@@@                                       ---@  @
            Runge_Kutta_4(Number_of_node,                                       //@@@   Runge-Kutta 4th Order Method  L2    ---@  @
                        data[3],                                                //@@@                                       ---@  @
                        coupling,                                               //@@@                                       ---@  @
                        frequency_layer2,                                       //@@@                                       ---@  @
                        inter_layer2,                                           //@@@                                       ---@  @
                        bdj_layer2,                                             //@@@                                       ---@  @
                        frust_layer2,                                           //@@@                                       ---@  @
                        Intrafrust_layer2,                                      //@@@                                       ---@  @
                        adj_layer2,                                             //@@@                                       ---@  @
                        Phases_layer2_previous,                                 //@@@                                       ---@  @
                        Phases_layer1_previous,                                 //@@@                                       ---@  @
                        Phases_next_layer2);                                    //@@@                                       ---@  @
            Phases_layer1_previous = for_loop_equal(Phases_next_layer1);        //@@@           Back to the future L1       ---@  @
            Phases_layer2_previous = for_loop_equal(Phases_next_layer2);        //@@@           Back to the future L2       ---@  @
            check_scale(Number_of_node,Phases_layer1_previous);                 //@@@       scale phases in -pi tp pi L1    ---@  @
            check_scale(Number_of_node,Phases_layer2_previous);                 //@@@       scale phases in -pi tp pi L2    ---@  @
            double syncrony_layer1 = order_parameter(Number_of_node,            //@@@                                       ---@  @
                                    Phases_layer1_previous);                    //@@@     order parameters (Synchroney) L1  ---@  @
            double syncrony_layer2 = order_parameter(Number_of_node,            //@@@                                       ---@  @
                                    Phases_layer2_previous);                    //@@@     order parameters (Synchroney) L2  ---@  @
            //------------------------------------------------------------------//@@@------------------------------------------@  @
            Phases_layer2 << time_loop << '\t';                                 //@@@                                       ---@  @
            Phases_layer1 << time_loop << '\t';                                 //@@@                                       ---@  @
            for (int i = 0; i < Number_of_node; i++){                           //@@@                                       ---@  @
                Phases_layer2 << std::fixed << std::setprecision(2) <<          //@@@                                       ---@  @
                                            Phases_layer2_previous[i] << '\t';  //@@@--->  print phase data in file .txt    ---@  @
                Phases_layer1 << std::fixed << std::setprecision(2) <<          //@@@                                       ---@  @
                                            Phases_layer1_previous[i] << '\t';  //@@@                                       ---@  @
            }                                                                   //@@@                                       ---@  @
            Phases_layer2 << endl;                                              //@@@                                       ---@  @
            Phases_layer1 << endl;                                              //@@@                                       ---@  @
            //------------------------------------------------------------------//@@@------------------------------------------@  @
            if (time_step>=Number_Steps_time_stationary){                       //@@@                                       ---@  @
                Total_syncrony_layer1 += syncrony_layer1;                       //@@@         calculate synchroney L1       ---@  @
                Total_syncrony_layer2 += syncrony_layer2;                       //@@@         calculate synchroney L2       ---@  @
            }                                                                   //@@@                                       ---@  @
            time_syncroney<<time_loop<< '\t'<<syncrony_layer1<< '\t'            //@@@   print synchrony data in file .txt   ---@  @
                          <<syncrony_layer2<<endl;                              //@@@                                       ---@  @
            //cout<<time_loop<< '\t'<<syncrony_layer1<< '\t'                    //@@@           cout synchrony data         ---@  @
                          //<<syncrony_layer2<<endl;                            //@@@                                       ---@  @
        }                                                                       //@@@                                       ---@  @
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        Total_syncrony_layer1=Total_syncrony_layer1/                            //@@@                                       ---@
                              (Number_Steps_time_stationary*4);                 //@@@    calculate total sync and pint it   ---@
        Total_syncrony_layer2=Total_syncrony_layer2/                            //@@@                                       ---@
                              (Number_Steps_time_stationary*4);                 //@@@                                       ---@
        time_t end = time(NULL);                                                //@@@             time of run               ---@
        cout<<"k=" <<strcoupling << '\t' <<"r="<< Total_syncrony_layer2 <<      //@@@       cout total synchrony data       ---@
        '\t' <<"Ex Time: "<< (double)(end-start)<<" Sec"<<endl;                 //@@@                                       ---@
        Average_Syncrony << strcoupling << '\t' << Total_syncrony_layer1 <<     //@@@          print total synchrony        ---@
                         '\t' << Total_syncrony_layer2<< '\t' <<                //@@@            data in file .txt          ---@
                         (double)(end-start) << endl;                           //@@@                                       ---@
        Phases_layer2.close();                                                  //@@@                                       ---@
        Phases_layer1.close();                                                  //@@@                                       ---@
    }                                                                           //@@@                                       ---@
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    ofstream Last_Phase_layer1("Save/Last_Phase/layer1.txt");                   //@@@                                       ---
    ofstream Last_Phase_layer2("Save/Last_Phase/layer2.txt");                   //@@@                                       ---
    for (int i = 0; i < Number_of_node; i++){                                   //@@@                                       ---
        Last_Phase_layer1 << Phases_layer1_previous[i] << endl;                 //@@@--->   print last coupling phases      ---
        Last_Phase_layer2 << Phases_layer2_previous[i] << endl;                 //@@@                                       ---
    }                                                                           //@@@                                       ---
    //--------------------------------------------------------------------------//@@@------------------------------------------
    Average_Syncrony.close();                                                   //@@@                                       ---
    Last_Phase_layer1.close();                                                  //@@@                                       ---
    Last_Phase_layer2.close();                                                  //@@@                                       ---
    delete Phases_layer1_previous;                                              //@@@                                       ---
    delete Phases_layer2_previous;                                              //@@@                                       ---
    delete Phases_next_layer1;                                                  //@@@                                       ---
    delete Phases_next_layer2;                                                  //@@@                                       ---
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                       ---                                                                             //@@@@                                   ---
    return 0;                                                                   //@@@     dont return any thing             ---
}                                                                               //@@@                                       ---
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@---
//-----------------------------------------------------------------------------------------------------------------------------
