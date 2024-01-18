


#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void RandomMatrix( int matrix[10][10], int size)
{
   
    for (int i = 0; i <size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            matrix[i][j]= rand() % 10;
        }
    }
}


void SeeMatrix(int matrix[10][10], int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            printf("%d ", matrix[i][j]);
           
        }
        printf("\n");
    }
}


void MultiplyMatrix(int mt1[10][10], int mt2[10][10], int answr[10][10], int row1,int col1, int row2,int col2)
{
    for(int i = 0; i < row1; i++)
    {
        for(int j = 0; j < col2; j++)
        {
            answr[i][j]=0;
            for(int k = 0; k < col1; k++)
            {
                answr[i][j] = answr[i][j] +mt1[i][k]*mt2[k][j];
            }
        }
    }
}


void ReadMatrixFromF(const char *file, int matrix[10][10], int *row, int *col)
{
    FILE *fp = fopen(file, "r");

    if(fp)
    {
        fscanf(fp, "%d %d", row, col);
        printf("Matrix read from file :\n");
        for (int i = 0; i < *row; i++)
        {
            for(int j = 0; j < *col; j++)
            {
                fscanf(fp, "%d", &matrix[i][j]);
                 printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
        fclose(fp);
    }else
    {
        printf("Error with file %s\n", file);
    }
}



int main()
{

    srand((unsigned int)time(NULL));
    int size;
    int matrix1[10][10], matrix2[10][10], answrMatrix[10][10];
    int rw1,cl1,rw2,cl2;
    printf("\n");
    printf("*************************************************************************************\n");
    printf("Enter a integer between 1 - 10 to specify the size of randomly\n"); 
    printf("generated matrices for multiplication. Alternatively, input the file path of two files containing matrices.\n");
    printf("Ensure each file starts with the size of the matrix, for example\n");
    printf("for a 2 by 3 matrix the first line of the file should contain '2 3' followed by\n");
    printf("the actual matrix on the next.\n");
    printf("*************************************************************************************\n");

    if (scanf("%d", &size) == 1)
    {
        if(size > 0 && size <= 10)
        {
           

            RandomMatrix(matrix1, size);
            RandomMatrix(matrix2, size);

            MultiplyMatrix(matrix1, matrix2, answrMatrix, size,size,size,size);
            
            printf("******************\n");
            printf("Matrix 1 =\n");
            SeeMatrix(matrix1, size);
            printf("******************\n");
            printf("\nMatrix 2 =\n");
            SeeMatrix(matrix2, size);
             printf("******************\n");
            printf("\nOutput Matrix =\n");
            SeeMatrix(answrMatrix, size);
            printf("******************\n");

           
        }
        else
        {
            printf("INVALID!!!!!: Size must be between 1 to 10.\n");
        }

    }
    else
    {
        char file1[50], file2[50];
        scanf("%s %s", file1, file2);

        ReadMatrixFromF(file1, matrix1, &rw1, &cl1);
        ReadMatrixFromF(file2, matrix2, &rw2, &cl2);

        if (cl1 != rw2)
        {
            printf("ERROR!!!: Matrices dimensions are not correct for multiplication.\n");
            printf("ERROR!!!:The number of columns in the first matrix is the same as the number of rows in the second matrix) \n");
            return 1;
        }

        MultiplyMatrix(matrix1, matrix2, answrMatrix, rw1,cl1,rw2,cl2);

        FILE *answrFile = fopen("matrix3.txt", "w");
        if(answrFile)
        {
            fprintf(answrFile, "%d by %d Matrix\n", rw1, cl2);
            for(int i = 0; i < rw1; i++)
            {
                for(int j = 0; j < cl2; j++)
                {
                    fprintf(answrFile, "%d ", answrMatrix[i][j]);
                }
                fprintf(answrFile, "\n");
            }
            fclose(answrFile);
           
            printf("\n Success! Matrix multiplication performed and result is saved to a file called matrix3.txt\n");
        }
        else
        {
            printf("ERROR!!!: Unable to open the output file.\n");
            return 1;
        }    
    }
    return 0;
}