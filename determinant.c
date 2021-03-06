#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void rewriteFromScannedArrayToMatrix(double*, double**, int);
void showMatrix(double**, int);
double det(double **, int);


int main (int argc, char **argv) {
    int maxIndex = 0, /* biggest index in a scannedArray array */
    i, j, /* counters */
    scanChecker, matrixDimension;
    double scannedValue, determinant;

    if(scanf("%d", &matrixDimension) < 1)
    {
      printf("Invalid size \r\n");
      exit(3);
    }
    printf("%d by %d\n", matrixDimension, matrixDimension);

 

    double **matrix;
    matrix = malloc(matrixDimension * sizeof(double *));
    if (!matrix)
	exit(3);
    for (i = 0; i < matrixDimension; i++)
    {
        matrix[i] = malloc (matrixDimension * sizeof (double));
        if(!matrix[i])
	{
	  for (j = 0; j < i; j++)
	    free(matrix[j]);
	  free(matrix);
	  abort();
	}
    }


    scanChecker = scanf("%lf", &scannedValue);
    i = 0, j = 0;

    
    while(scanChecker != EOF)
    {
	if (scanChecker == 0)
	{
	  printf("INCORRECT INPUT\n");
	  for (i = 0; i < matrixDimension; i++)
	    free(matrix[i]);
	  free(matrix);
	  abort();
	}
        matrix[i][j] = scannedValue;
        scanChecker = scanf("%lf", &scannedValue);
        if (scanChecker == 1)
            maxIndex++;
        j++;
        if (maxIndex % matrixDimension == 0)
            i++, j = 0;
    }

    if (sqrt(maxIndex+1) == (int)sqrt(maxIndex+1))
        printf("The matrix is rectangular.\n");

    //showMatrix(matrix, matrixDimension);

    determinant = det(matrix, matrixDimension);

    printf("determinant of a matrix: %f", determinant);
    printf("\n\n");

    for (i = 0; i < matrixDimension; i++)
        free(matrix[i]);
    free(matrix);
    return 0;
}


double det(double **matrix, int matrixDimension)
{
    int i, j, except; /* counters */
    double sum = 0;

    if (matrixDimension == 1)
        return matrix[0][0];
    else if (matrixDimension == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    else
    {
        double **minorMatrix;
        minorMatrix = malloc((matrixDimension - 1) * sizeof(double *));
	if (!minorMatrix) abort();
        for (i = 0; i < matrixDimension - 1; i++)
        {
            minorMatrix[i] = malloc ((matrixDimension - 1) * sizeof (double));
            if(!minorMatrix[i]) abort();
        }

        for (except = 0; except < matrixDimension; except++)
        {
            for (i = 1; i < matrixDimension; i++)
                for (j = 0; j < matrixDimension; j++)
                {
                    if (j < except)
                        minorMatrix[i - 1][j] = matrix[i][j];
                    else if (j > except)
                        minorMatrix[i - 1][j - 1] = matrix[i][j];
                }
            sum += pow(-1, except) * matrix[0][except] * det(minorMatrix, matrixDimension - 1);
        }
        for (i = 0; i < matrixDimension - 1; i++)
            free(minorMatrix[i]);
        free(minorMatrix);
        return sum;
    }
}


void showMatrix(double **matrix, int matrixDimension)
{
    int i, j; /* counters */

    printf("\t===MATRIX===\n");
    for(i = 0; i < matrixDimension; i++)
    {
        for(j = 0; j < matrixDimension; j++)
                printf("%f ", matrix[i][j]);
        printf("\n");
    }
}
