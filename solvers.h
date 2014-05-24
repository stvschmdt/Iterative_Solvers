#ifndef __SOLVER_HEADER_H__ 
#define __SOLVER_HEADER_H__ 

#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<time.h>
#include<math.h>

#define JACOBI 0
#define GSM 1
#define SOR 2
#define DIRICHILET 0
#define MAX_ITERS 1000
/* Parameters */
typedef struct{
    int x;        // x-matrix dimensions
    int y;        // y-matrix dimensions
    int z;        // z-matrix dimensions
    double p_x;   // Physical Domain Length
    double p_y;   // Physical Domain Length
    double p_z;   // Physical Domain Length
    double dt;    // Timestep length
    double dx;    // grid space length
    int NT;       // Number of timesteps
    double alpha; // alpha
} Params;


// init.c
Params read_params(int argc, char * argv[]);
void read_file_params(Params * params);
void print_Slice(double ***Matrix, Params params, int t);
// main.c
double *** allocate_matrix(int x, int y, int z); 
void free_matrix(double ***M); 
void gaussian(double *** M, Params params); 

// jocobi
void jacobi_solver( double *** Matrix, Params params );
double check_Tolerance(double ***M, double ***Mp, Params params);

//gsm
void gsm_solver( double *** Matrix, Params params );

//sor
void sor_solver( double *** Matrix, Params params );
#endif
