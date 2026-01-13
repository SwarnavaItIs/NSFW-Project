/* Program to store coordinates and calculate center of mass */

#include <stdio.h>    // Standard input/output functions
#include <string.h>   // String handling functions
#include <stdlib.h>   // Standard utility functions
#include <ctype.h>    // Character type functions
#include <math.h>     // Mathematics functions

int main()
{
    FILE *fpt1, *fpt2;

    int i, l, c1;
    int store_atm_num[20000], store_res_num[20000];

    char line[200], word[5], x[9], sl_num[6];
    char atn_name[4], res_name[4], res_num[5];
    char chain_id[20000];
    char store_atn_name[20000][4], store_res_name[20000][4];

    float store_x[20000], store_y[20000], store_z[20000];
    float total_x = 0.0, total_y = 0.0, total_z = 0.0;
    float cm_x, cm_y, cm_z;

    /* Open input and output files */
    fpt1 = fopen("3inp.pdb", "r");   // Read input file
    fpt2 = fopen("out.pdb", "w");    // Output file

    if (fpt1 == NULL || fpt2 == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    c1 = 0;

    /* Read file line by line */
    while (fgets(line, 200, fpt1) != NULL)
    {
        /* Store first four characters */
        for (l = 0; l < 4; l++)
            word[l] = line[l];
        word[4] = '\0';

        /* Compare ATOM record */
        if (strcmp(word, "ATOM") == 0)
        {
            /* Store atom number */
            for (l = 0; l < 5; l++)
                sl_num[l] = line[l + 6];
            sl_num[5] = '\0';
            store_atm_num[c1] = atoi(sl_num);

            /* Store atom name */
            for (l = 0; l < 3; l++)
                atn_name[l] = line[l + 13];
            atn_name[3] = '\0';
            strcpy(store_atn_name[c1], atn_name);

            /* Store residue name */
            for (l = 0; l < 3; l++)
                res_name[l] = line[l + 17];
            res_name[3] = '\0';
            strcpy(store_res_name[c1], res_name);

            /* Store chain ID */
            chain_id[c1] = line[21];

            /* Store residue number */
            for (l = 0; l < 4; l++)
                res_num[l] = line[l + 22];
            res_num[4] = '\0';
            store_res_num[c1] = atoi(res_num);

            /* Store X coordinate */
            for (l = 0; l < 8; l++)
                x[l] = line[l + 30];
            x[8] = '\0';
            store_x[c1] = atof(x);

            /* Store Y coordinate */
            for (l = 0; l < 8; l++)
                x[l] = line[l + 38];
            x[8] = '\0';
            store_y[c1] = atof(x);

            /* Store Z coordinate */
            for (l = 0; l < 8; l++)
                x[l] = line[l + 46];
            x[8] = '\0';
            store_z[c1] = atof(x);

            /* Write ATOM line to output file */
            fprintf(fpt2, "%s", line);

            c1++;
        }
    }

    /* Calculate center of mass */
    for (i = 0; i < c1; i++)
    {
        total_x += store_x[i];
        total_y += store_y[i];
        total_z += store_z[i];
    }

    cm_x = total_x / c1;
    cm_y = total_y / c1;
    cm_z = total_z / c1;

    printf("Center of Mass:\n");
    printf("Xcm = %f\n", cm_x);
    printf("Ycm = %f\n", cm_y);
    printf("Zcm = %f\n", cm_z);

    fclose(fpt1);
    fclose(fpt2);

    return 0;
}