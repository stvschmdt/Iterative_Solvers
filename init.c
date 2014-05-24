#include "solvers.h"


/* Handles all input reading & verification etc */
Params read_params(int argc, char * argv[])
{
    Params params;
    read_file_params(&params);
    params.dx = params.p_x / params.x;
    return params;
}


/* Reads Input Parameters From File "settings.txt" */
void read_file_params(Params * params)
{
    FILE * fp = fopen("parameters", "r");
    char c[255];

    fscanf(fp, "%d", &params->x);
    fgets(c, 255, fp);
    fscanf(fp, "%d", &params->y);
    fgets(c, 255, fp);
    fscanf(fp, "%d", &params->z);
    fgets(c, 255, fp);
    fscanf(fp, "%lf", &params->p_x);
    fgets(c, 255, fp);
    fscanf(fp, "%lf", &params->p_y);
    fgets(c, 255, fp);
    fscanf(fp, "%lf", &params->p_z);
    fgets(c, 255, fp);
    fscanf(fp, "%lf", &params->alpha);
    fgets(c, 255, fp);
    fscanf(fp, "%lf", &params->dt);
    fgets(c, 255, fp);
    fscanf(fp, "%d", &params->NT);
    fgets(c, 255, fp);
}

/* Allocates a 3D contiguous matrix of doubles */
double *** allocate_matrix(int x, int y, int z)
{
    double * data = (double *) malloc( x*y*z * sizeof(double));
    double ** d2 = (double ** ) malloc( x*y * sizeof(double *));
    double *** matrix = (double *** ) malloc( x * sizeof(double **));

    assert(data != NULL);
    assert(d2 != NULL);
    assert(matrix != NULL);

    for( int i = 0; i < x*y; i++ )
	d2[i] = &data[i*z];

    for( int i = 0; i < x; i++ )
	matrix[i] = &d2[i*y];

    return matrix;
}

/*init gaussian*/
void gaussian(double *** M, Params params)
{
    srand(1);
    for( int i = 0; i < params.x; i++ )
    {
	double x = i*params.dx - params.p_x/2.0;
	for( int j = 0; j < params.y; j++ )
	{
	    double y = j*params.dx - params.p_y/2.0;
	    for( int k = 0; k < params.z; k++ )
	    {
		double z = k*params.dx - params.p_z/2.0;
		M[i][j][k] = exp(-pow(x,2)-pow(y,2)-pow(z,2))+.09*rand()/RAND_MAX;
	    }
	}
    }
}

void print_Slice(double ***Matrix, Params params, int t)
{
    int i, j, k;
    FILE *init;
    for(  i = 0; i < params.x; i++ )
    {
	for(  j = 0; j < params.y; j++ )
	{
	    for(  k = 0; k < params.z; k++ )
	    {
		if(k==t){
		    init = fopen ("graph.txt", "a");
		    fprintf(init, "%lf %lf %lf %c",params.dx*(double)i, params.dx*(double)j, Matrix[i][j][k],'\n' );
		    fclose(init);

		}
	    }
	}
    }
}


void free_matrix(double ***M)
{
    free(M[0][0]);
    free(M[0]);
    free(M);
}
