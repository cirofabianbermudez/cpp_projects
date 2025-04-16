//=============================================================================
// [Filename]       main.cpp
// [Project]        hits_uvc
// [Author]         Ciro Bermudez - cirofabian.bermudezmarquez@ba.infn.it
// [Language]       C++ 17
// [Created]        March 2025
// [Modified]       -
// [Description]    C++ code to generate file for UVM sequence read from file
// [Notes]          -
// [Status]         stable
// [Revisions]      -
//=============================================================================

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <thread>
#include <chrono>

int main(){

    // Open a pipe to gnuplot.
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        std::cerr << "Error: Could not open pipe to gnuplot." << std::endl;
        return 1;
    }

    // Set up the plot (titles, axis, etc.).
    fprintf(gnuplotPipe, "set title 'Real-Time Data from C++'\n");
    fprintf(gnuplotPipe, "set xlabel 'X-axis'\n");
    fprintf(gnuplotPipe, "set ylabel 'Y-axis'\n");

    double amp = 1.0;
    // Continuously generate data and send to gnuplot.
    while (true) {
        // Tell gnuplot to expect inline data.
        fprintf(gnuplotPipe, "plot '-' using 1:2 with lines title 'Generated Data'\n");

        // For demonstration, generate some data points (e.g., sine wave).
        for (double x = 0.0; x <= 10.0; x += 0.001) {
            double y = sin(amp*x);  // Replace with your data generation logic.
            fprintf(gnuplotPipe, "%lf %lf\n", x, y);
        }
        // Signal the end of inline data.
        fprintf(gnuplotPipe, "e\n");
        fflush(gnuplotPipe);

        // Pause briefly before updating.
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        amp += 1.0;
        if (amp > 10.0) break;
    }

    // Close the pipe when finished (won't be reached in this infinite loop).
    pclose(gnuplotPipe);


  return 0;
}