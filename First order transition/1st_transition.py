import numpy as np
import time
start_time=time.time() 


def read_2d_array(file_name):
    path="./inputs/"+file_name+".txt"
    data = np.loadtxt(path)
    return data

def read_1d_array(file_name):
    path="./inputs/"+file_name+".txt"
    data = np.loadtxt(path)
    return data

def Kuramoto (w, theta, K, A):
    N=len(theta)
    dtheta_dt=np.zeros(N)
    for i in range (0,N,1):
        Sigma=0
        for j in range (0,N,1):
            Sigma=Sigma+A[i][j]*np.sin(theta[j]-theta[i])
        dtheta_dt[i]=w[i]+(K/N)*Sigma
    return dtheta_dt


def order_parameter (theta):
    N=len(theta)
    r_cos=0
    r_sin=0
    r=0
    r_cos=(1/N)*sum(np.cos(theta))
    r_sin=(1/N)*sum(np.sin(theta))
    r=np.sqrt(pow(r_cos,2)+pow(r_sin,2))
    return r


def r_total (r):
    count = 0
    order_parameter = 0
    n_step = len(r)                                   # we produce r for each step. So the length of r is number of steps.
    for i in range (int((2/5)*n_step),n_step):
        order_parameter = order_parameter + r[i]
        count = count + 1
    return (order_parameter/count)


def rk_4(Adj, omega, theta_initial, t_final, dt, J_intial, J_final, dJ ):
    t_start_save = int((4/5)*t_final)
    N = len(theta_initial)
    theta_old = np.zeros(N)
    theta_new = np.zeros(N)
    theta_old = theta_initial
    r_j = np.zeros(J_final)                                  # r_k is Order parameter that refers to each coupling strength. (201 different couplings)
    count_ = 0
    with open('./outputs/r_j/r_j.txt', 'w') as file0:
        for j_loop in range (J_intial, J_final, dJ):
            j=j_loop/100
            k=j*(np.sqrt(8/np.pi))
            
            theta_old = theta_initial
            #in the all code use j else in RK4                                  
            syncrony = np.zeros(t_final)
            with open('./outputs/r_t/r_t_J='+str(j)+'.txt', 'w') as file2:
                for t in range (0,t_final,1):        
                    k1 = dt * Kuramoto(omega, theta_old, k, Adj)                         # Runge Kutta method
                    k2 = dt * Kuramoto(omega, theta_old + k1/2, k, Adj)
                    k3 = dt * Kuramoto(omega, theta_old + k2/2, k, Adj)
                    k4 = dt * Kuramoto(omega, theta_old + k3, k, Adj)
                    theta_new = theta_old + (1/6)*(k1 + 2*k2 + 2*k3 + k4)
                    #theta_new=theta_old+Kuramoto(omega, theta_old, coupling, Adj)*dt           # Euler's method
                    theta_old = theta_new
                    syncrony[t] = order_parameter(theta_new)
                    # Write t and theta_new to the file
                    file2.write(f'{t}\t{syncrony[t]}\n')
            r_j[count_] = r_total(syncrony)
            print(j,"\t",k,"\t",r_j[count_])
            file0.write(f'{j}\t{r_j[count_]}\t{"{:.3f}".format(time.time()-start_time)}\n')
            count_ = count_ + 1
    pass



def main():
    Adj = read_2d_array("Matrix_new1")
    omega = read_1d_array("w")
    theta_initial = read_1d_array("theta")
    t_final = 10
    dt = 0.01
    J_intial = 0
    J_final = 300
    dJ = 1
    rk_4(Adj, omega, theta_initial, t_final, dt, J_intial, J_final, dJ)
    pass



if __name__=="__main__":
    main()