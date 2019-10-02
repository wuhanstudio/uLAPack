/**
 * @name polyfit.c
 * An example of using uLAPAck for polynomial regression.
 *
 * @note In this example, static memory allocation is used
 *       via the -D compiler options.
 * @note Build this example using: $ make polyfit
 * @note Run this example using: $ ./polyfit
 */

#include "ulapack.h"
#include <rtthread.h>
#include <stdio.h>
#include <time.h>

/**
 * @name run_regression
 * A helper function to regress some data.
 *
 * @param[in] xdata The x coordinate data.
 * @param[in] ydata The y coordinate data.
 * @param The number of x and y points.
 * @param nth_degree The number of degrees to fit a polynomial to.
 * @param[out] polynomial_coefs The returning polynomial fit coefficients.
 */
static void run_regression(const MatrixEntry_t * xdata, 
                           const MatrixEntry_t * ydata, 
                           const Index_t data_points, 
                           const Index_t nth_degree,
                           Matrix_t * const polynomial_coefs) {
    /*
     * Declare matrix objects.
     */
    Matrix_t* x = RT_NULL;
    Matrix_t* y = RT_NULL;

    /*
     * Initialize matrix objects.
     */
    ulapack_init(&x, data_points, 1);
    ulapack_init(&y, data_points, 1);

    /*
     * Copy data points into vector objects.
     */
    ulapack_array_col_copy(ydata, y, 0, data_points);
    ulapack_array_col_copy(xdata, x, 0, data_points);

    /*
     * Run the regression.
     */
    ulapack_polyfit(x, y, nth_degree, polynomial_coefs);
}

void ulapack_polyfit_thread_entry(void* parameters) {
    clock_t start, end;
    float cpu_time_used;
    start = clock();

    MatrixEntry_t xdata[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    /*
     * x^2 + noise
     */
    MatrixEntry_t ydata[] = {0.679196, 3.215585, 
                             8.635037, 16.117271, 
                             25.174340, 35.784344, 
                             48.847389, 64.033688, 
                             81.458282, 101.281631};

    const Index_t degree = 2;
    Matrix_t* p = RT_NULL;

    ulapack_init(&p, degree + 1, 1);

    run_regression(xdata, ydata, 10, 2, p);

    printf("\nFit coefficients: \n");
    ulapack_print(p, stdout);

    end = clock();
    cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
    printf("[ulapack] Total speed was %f ms\n", cpu_time_used * 1000);
}

static void ulapack_polyfit_example(int argc, char *argv[])
{
    rt_thread_t thread = rt_thread_create("u_poly", ulapack_polyfit_thread_entry, RT_NULL, 2048, 25, 10);
    if(thread != RT_NULL)
    {
        rt_thread_startup(thread);
        rt_kprintf("[ulapack] New thread pca\n");
    }
    else
    {
        rt_kprintf("[ulapack] Failed to create thread pca\n");
    }
}
MSH_CMD_EXPORT(ulapack_polyfit_example, ulapack polyfit example);

/*
 * Corresponding MATLAB code for comparison.
 */

/*

clear all;
close all;
clc;

x = [1:1:10]';

%% Noisy x^2
y = [0.679196;
    3.215585;
    8.635037; 
    16.117271; 
    25.174340; 
    35.784344; 
    48.847389; 
    64.033688; 
    81.458282,
    101.281631];

p = polyfit(x, y, 2)';

ulap_p = [1.02164869318180340229673674912191927433013916015625;
         -0.09319982499999923675204627215862274169921875;
         -0.2981993499998480956492130644619464874267578125];

error = norm(p - ulap_p);

figure()
plot(x, y, 'o');
hold on;
plot(linspace(1, 10), polyval(p, linspace(1,10)))
hold on;
plot(linspace(1, 10), polyval(ulap_p, linspace(1,10)))

leg = legend('Actual Data', 'MATLAB', '$\mu$LAPack polyfit');
set(leg, 'FontSize', 12, 'Interpreter', 'Latex');

title('Comparing MATLAB and $\mu$LAPack Polynomial Fitting (Noisy $x^2$)', ...
'Interpreter', 'Latex', 'FontSize', 16)
xlabel('$x$', 'Interpreter', 'Latex', 'FontSize', 20)
ylabel('$y$', 'Interpreter', 'Latex', 'FontSize', 20)

grid on

fprintf('\nResidual Error = %f\n\n', error)

*/
