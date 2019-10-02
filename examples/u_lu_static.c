/**
 * @name lu.c
 * An example of using uLAPAck for lu matric decomposition.
 *
 * @note In this example, static memory allocation is used
 *       via the -D compiler options.
 */

#include "ulapack.h"
#include <rtthread.h>
#include <stdio.h>
#include <time.h>

static void run_lu(double Amatrix[4][4]) 
{
    MatrixError_t ret;

    Matrix_t A;
    Matrix_t U;
    Matrix_t L;

    ulapack_init(&A, 4, 4);
    ulapack_init(&U, 4, 4);
    ulapack_init(&L, 4, 4);

    /*
     * Copy data points into vector objects.
     */
    for (Index_t row_itor = 0; row_itor < 4; row_itor++) {
        for (Index_t col_itor = 0; col_itor < 4; col_itor++) {
            ulapack_edit_entry(&A, 
            row_itor, col_itor, 
            Amatrix[row_itor][col_itor]);
        }
    }

    ret = ulapack_lu(&A, &U, &L);
    if(ret != ulapack_success)
    {
        printf("[ulapack] LU Failed\n");
    }

    printf("\nA = \n");
    ulapack_print(&A, stdout);

    printf("\nU = \n");
    ulapack_print(&U, stdout);

    printf("\nL = \n");
    ulapack_print(&L, stdout);
}

static void ulapack_lu_thread_entry(void* parameters) 
{
    clock_t start, end;
    float cpu_time_used;
    start = clock();

    double Adata[4][4] = { 2, 7, 6, 2,
                           9, 5, 1, 3,
                           4, 3, 8, 4,
                           5, 6, 7, 8
    };
    run_lu(Adata);
    end = clock();
    cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
    printf("[ulapack] Total speed was %f ms\n", cpu_time_used * 1000);

    // Uncomment this if you'd like to check memory usage with list_thread
    while(1)
    {
        rt_thread_mdelay(500);
    }
}

static void ulapack_lu_example(int argc, char *argv[])
{
    rt_thread_t thread = rt_thread_create("u_lu", ulapack_lu_thread_entry, RT_NULL, 15360, 25, 10);
    if(thread != RT_NULL)
    {
        rt_thread_startup(thread);
        rt_kprintf("[ulapack] New thread lu\n");
    }
    else
    {
        rt_kprintf("[ulapack] Failed to create thread lu\n");
    }
}
MSH_CMD_EXPORT(ulapack_lu_example, ulapack LU decomposition example);

/*
 * Corresponding MATLAB code for comparison.
 */

/*

clear all;
close all;
clc;

A = [2, 7, 6, 2;
     9, 5, 1, 3;
     4, 3, 8, 4;
     5, 6, 7, 8]

[L, U, P] = lu(A)

*/
