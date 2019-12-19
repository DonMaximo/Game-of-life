#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#define M 40
#define N 80
#define N_INIT_CONFIG   8
#define ALIVE 1
#define DEAD 0
void clearScreen(void);

// display the game borad 
void display(int m, int n, int A[][n])
{
    int i, j;

    for(i=0; i<m; i++)
    {
        for(j=0; j<n; j++)
        {
            if(A[i][j] == 1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
}

// copy a small board into a bigger game board
void copy_block(int m, int n, int source[][n], int i_d, int j_d, int m1, int n1, int dest[][n1])
{
    int i, j;

    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
        {
            if(i_d + i < m1 && j_d + j < n1)
                dest[i_d + i][j_d + j] = source[i][j];		
        }
}

int mod(int a, int b)
{
    int r= a%b;
    return r < 0 ? r+b : r;
}
int check_state(int i, int j, int n, int current_gen[][n])
{
    if (current_gen[i][j] == ALIVE)
        return ALIVE;
    else
        return DEAD;
}

int check_neighbors(int i, int j, int m, int n , int current_gen[][n])
{
    int f =0;
    int neighbors=0; 
    int i1 = mod(i-1,m);
    int j1 = mod(j-1,n);

    int i2 = mod(i+1,m);
    int j2 = mod(j+1,n);

    do
    {
       neighbors += check_state(i1,j1,n,current_gen);
       neighbors += check_state(i1,j,n,current_gen);
       neighbors += check_state(i1,j2,n,current_gen);
       neighbors += check_state(i,j1,n,current_gen);
       neighbors += check_state(i,j2,n,current_gen);
       neighbors += check_state(i2,j1,n,current_gen);
       neighbors += check_state(i2,j,n,current_gen);
       neighbors += check_state(i2,j2,n,current_gen);

    }while(f);

    return neighbors;
}

void next_generation(int m, int n, int A[][n])
{
    int i,j;
    int num_neighbors=0;
    int state;
    int current_gen[m][n];
    
    for (i=0; i<m; i++)
        for (j=0; j<n; j++)
            current_gen[i][j] = A[i][j];
    
   
    for (i =0; i <m; i++)   
        for (j=0; j<n; j++)
        {
            state = current_gen[i][j];
            num_neighbors=check_neighbors(i,j,m,n,current_gen);
  //          printf("(i,j) = (%d,%d)\n",i,j);
//            printf("neighbors @ i,j = %d\n",num_neighbors);

            switch(state)
            {
                case(ALIVE):
                    if (num_neighbors==0 || num_neighbors==1)
                        A[i][j]= DEAD;
                       
                    
                    if (num_neighbors >= 4)                 
                        A[i][j] = DEAD;
   
//                        display(m,n,current_gen);
                    
                    if (num_neighbors ==2 || num_neighbors ==3)
                         A[i][j] = ALIVE;
                    break;
                       
                    
                case (DEAD):
                    if (num_neighbors ==3) 
                         A[i][j] = ALIVE;
                    break;
    
      //      assert(A[19][41] == 1);
    //        printf("true");
                    
            }
         }

}

int main(int argc, char ** argv)
{
    // initialize all elements in A to 0
    int A[M][N] = {{0}};
    // hard coded configuration. 
    int a[10][10] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
    };
    int b[5][5] = {
        {0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0}, 
        {0, 1, 1, 1, 0}, 
        {0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0}
    };
    int c[2][2] = {{1, 1}, {1, 1}};
    int d[3][3] = {{0, 1, 1}, {1, 1, 0}, {0, 1, 0}};
    int e[3][8] = {{0, 0, 0, 0, 0, 0, 1, 0}, {1, 1, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 1, 1, 1}};
    int f[3][7] = {{0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0}, {1, 1, 0, 0, 1, 1, 1}};
    int g[6][9] = {
        {0,0,0,0,0,0,0,1,0},
        {0,0,0,0,0,1,0,1,1},
        {0,0,0,0,0,1,0,1,0},
        {0,0,0,0,0,1,0,0,0},
        {0,0,0,1,0,0,0,0,0},
        {0,1,0,1,0,0,0,0,0}
    };
    int h[3][4] = {{0, 0, 1, 0}, {0, 0, 0, 1}, {0, 1, 1, 1}}; 

    if (argc == 1) {
        printf("Usage: %s init_conf [num_generations]\n", argv[0]);
        return 1;
    }

    // now, argc must be >= 2
    int init_conf = atoi(argv[1]);
    if (init_conf > N_INIT_CONFIG || init_conf < 1) {
        printf("init_conf must be an integer that is  >= 1 and <= 8.\n"); 
        return -1;
    }

    // set up the initial configuration
    switch(init_conf)
    {
        case 1:	
            copy_block(10, 10, a, M/2, N/2, M, N, A);
            break;
        case 2:
            copy_block(5, 5, b, M/2, N/2, M, N, A);
            break;
        case 3:
            copy_block(2, 2, c, M/2, N/2, M, N, A);
            break;
        case 4:
            copy_block(3, 3, d, M/2, N/2, M, N, A);
            break;
        case 5:
            copy_block(3, 8, e, M/2, N/2, M, N, A);
            break;
        case 6:
            copy_block(3, 7, f, M/2, N/2, M, N, A);
            break;
        case 7:
            copy_block(6, 9, g, M/2, N/2, M, N, A);
            break;
        case 8:
            copy_block(3, 4, h, M/2, N/2, M, N, A);
            break;
        default: 
            // should never get here 
            printf("Error: Invalid init_conf.\n");
            return -1;
    }

    int num_generations;

    if (argc >= 3) {
        num_generations = atoi(argv[2]); 
        if (num_generations <= 0) {
            printf("Error: Number of generations must be an integer > 0.\n");
            return 1;
        }
        for (int i=0; i < num_generations; i++) {
            next_generation(M, N, A);
        }
        display(M, N, A);
    }
    else {
        // interactive
        clearScreen();
        display(M, N, A);
        int rv = 1;

        while (rv == 1) {
            printf("Enter an integer (number of generations):");
            fflush(stdout); // flush stdout to display the prompt w/o new line 
            rv = scanf("%d", &num_generations);
            if (rv == 1 && num_generations > 0) {
                for (int i=0; i < num_generations; i++) {
                    clearScreen();
                    next_generation(M, N, A);
                    display(M, N, A);
                    usleep(50000);
                }
            }
            else if (rv == 0) {
                printf("Error: Number of generations must be an integer > 0.\n");
                return 1;
            }
        }
        if (rv < 0)
            printf("\n");
    }

    return 0;
}


// Use ANSI control sequence to clear screen
void clearScreen(void)
{
    char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    printf("%s", CLEAR_SCREEN_ANSI);
    fflush(stdout);
}

