#include "solvers.h"

int main(int argc, char * argv[])
{
	Params params = read_params(argc, argv);
	
	// Initialize Domain and Apply Gaussian
	double *** M = allocate_matrix(params.x, params.y, params.z);
	gaussian(M, params);


	// Start timer
	time_t start, end;
	double time_J, time_G, time_S;
	start = clock();
        jacobi_solver(M, params);
	end = clock();
	time_J = ((double)end-start) / (double) CLOCKS_PER_SEC;
	printf("Runtime for Jacobi:  %.3f seconds\n", time_J);
	start = clock();
        gsm_solver(M, params);
	end = clock();
	time_G = ((double)end-start) / (double) CLOCKS_PER_SEC;
	printf("Runtime for Gauss-Seidel:  %.3f seconds\n", time_G);
	start = clock();
        sor_solver(M, params);
	end = clock();
	time_S = ((double)end-start) / (double) CLOCKS_PER_SEC;
	printf("Runtime for Successive Over Relaxation:  %.3f seconds\n", time_S);

	
	// Print Timing Results
	printf("Simulation Complete...\n");
	printf("Simulations Time per timestep\n1) Jacobi 2) GSM 3) SOR\n");
	printf("%f\n%f\n%f\n", time_J / (double)params.NT, time_G / (double)params.NT, time_S / (double)params.NT);

	// Free Matrix
	free_matrix(M);

	return 0;
}
