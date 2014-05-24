#include "solvers.h"

void jacobi_solver( double *** Matrix, Params params )
{
    printf("Beginning simulation using Jacobi method...\n");

    double up = 0;
    double down = 0;
    double left = 0;
    double right = 0;
    double front = 0;
    double back = 0;
    double C = params.dt * params.alpha / pow(params.dx,2);
    int i, j, k, n, t;
    double *** M = allocate_matrix(params.x, params.y, params.z);
    double *** Mp = allocate_matrix(params.x, params.y, params.z);
    double *** Mt = allocate_matrix(params.x, params.y, params.z);
    memcpy( M[0][0], Matrix[0][0], params.x*params.y*params.z * sizeof(double));
    memcpy( Mp[0][0], Matrix[0][0], params.x*params.y*params.z * sizeof(double));
    memcpy( Mt[0][0], Matrix[0][0], params.x*params.y*params.z * sizeof(double));
    
    for(  n = 0; n < params.NT; n++ )
    {
	double ***inittmp = Mp;
	Mp = Mt;
	Mt = inittmp;
	for( t = 0;t < MAX_ITERS ; t++)
	{

	    for(  i = 0; i < params.x; i++ )
	    {	    

		for(  j = 0; j < params.y; j++)
		{

		    for(  k = 0; k < params.z; k++ )
		    {
			if(i == 0){
			    up = 0;
			}
			else{
			    up = Mp[i-1][j][k];
			}
			if(i == params.x-1){
			    down = 0;
			}
			else{
			    down = Mp[i+1][j][k];
			}
			if(j == 0){
			    front = 0;
			}
			else{
			    front = Mp[i][j-1][k];
			}
			if(j == params.y-1){
			    back = 0;
			}
			else{
			    back = Mp[i][j+1][k];
			}
			if(k == 0){
			    left = 0;
			}
			else{
			    left = Mp[i][j][k-1];
			}
			if(k == params.z-1){
			    right = 0;
			}
			else{
			    right = Mp[i][j][k+1];
			}
			M[i][j][k] = (C /(6.0*C+1.0)) * ( up + down + right + left + front + back) + ((1.0/(6.0*C+1.0)) * Mt[i][j][k] );
		    }
		}
	    }
	    double ***itertmp = M;
	    M = Mp;
	    Mp = itertmp;
	    if(check_Tolerance(M, Mp, params) < 1.0e-6){
		break;
	    }

	}   
    if( n == 900){
    }	//switch time periods
	double ***timetmp = Mt;
	Mt = Mp;
	Mp = timetmp;
    }
	print_Slice(Mp, params, params.z/2);

    free_matrix(Mp);
    free_matrix(M);
}

double check_Tolerance(double ***M, double ***Mp, Params params){
    double diff = 0.0;
    int i, j, k;
    for(  i = 0; i < params.x; i++ )
    {   
	for(  j = 0; j < params.y; j++ )
	{
	    for(  k = 0; k < params.z; k++ )
	    {	    
		diff += fabs(M[i][j][k] - Mp[i][j][k]);
	    }
	}
    }
    return diff;
}
