#include <stdlib.h>
#include <stdio.h>

int **createLevelTileMatrix(char *path, int rows, int collumns, int **tileMatrix)
{
    tileMatrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        tileMatrix[i] = (int *)malloc(collumns * sizeof(int));
    }
    

    FILE *mapFile = fopen( path, "r" );
    
    if( mapFile == NULL ){
        fprintf( stderr, "Failed to open file %s", path );
        return NULL;
    }
    
    char line[100]; int i;
    while( fgets( line, 100, mapFile ) != NULL )
    {
        if( line[0] == ';')
            continue;

        for ( int j = 0; j < collumns; j++ )
        {
            tileMatrix[i][j] = line[j] - '0';
        }

        i++;
        
    }

    if( fclose( mapFile ) == EOF ){
        fprintf( stderr, "Failed to close file %s", path );
        return NULL;
    }

    free(mapFile);

    return tileMatrix;
}

/*
int main(void){
    int **map = NULL;
    map = createLevelTileMatrix("test_map.txt", 5, 5, map);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", map[i][j]);
        }
        puts("");
    }  
}
*/