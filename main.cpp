// Sources: https://www.geeksforgeeks.org/c/how-to-create-dynamic-array-inside-structure-in-c/,
// https://cplusplus.com/doc/tutorial/structures
//https://cplusplus.com/doc/tutorial/control/
//AI sources: Chat GPT, Claude AI


#include <iostream>

using namespace std;

struct _capacitor // holds the data for a capacitor
{
    double* time; // pointer to the time
    double* voltage; // pointer to the voltage
    double* current; // pointer to the current
    double C; // capacitance in farads
};

typedef struct _capacitor Capacitor;

int main()
{
    const int steps = 50000; // Number of time steps
    const double dt = 1e-10; // Time step in seconds
    const double R = 1000.0; // Resistance in OHMS
    const double V0 = 10.0; // Supply voltage in volts
    const double C = 100e-12; // Capacitance in farads
    const double I0 = 1e-2; // Constant current in amps

    Capacitor constantCurrent;
    Capacitor constantVoltage;

    constantCurrent.C = C;
    constantVoltage.C = C;

    // Allocate arrays (steps + 1 for initial condition)
    constantCurrent.time = new double[steps + 1];
    constantCurrent.voltage = new double[steps + 1];
    constantCurrent.current = new double[steps + 1];

    constantVoltage.time = new double[steps + 1];
    constantVoltage.voltage = new double[steps + 1];
    constantVoltage.current = new double[steps + 1];

    // Initial conditions for constant current capacitor
    constantCurrent.time[0] = 0.0;
    constantCurrent.voltage[0] = 0.0;
    constantCurrent.current[0] = I0;

    // Initial conditions for constant voltage capacitor
    // At time 0, voltage is 0 and current is V0/R
    constantVoltage.time[0] = 0.0;
    constantVoltage.voltage[0] = 0.0;
    constantVoltage.current[0] = V0 / R;

    // Calculate voltage and current at each timestep
    for (int step = 1; step <= steps; step++)
    {
        // Constant current capacitor
        constantCurrent.time[step] =
            constantCurrent.time[step - 1] + dt;

        // V(t+1) = V(t) + I(t) * dt / C
        constantCurrent.voltage[step] =
            constantCurrent.voltage[step - 1]
            + constantCurrent.current[step - 1] * dt
            / constantCurrent.C;

        // Current stays constant
        constantCurrent.current[step] = I0;

        // Constant voltage capacitor
        constantVoltage.time[step] =
            constantVoltage.time[step - 1] + dt;

        // I(t+1) = I(t) - I(t) * dt / (R * C)
        constantVoltage.current[step] =
            constantVoltage.current[step - 1]
            - constantVoltage.current[step - 1] * dt
            / (R * constantVoltage.C);

        // Calculate voltage using Kirchhoff's Voltage Law
        constantVoltage.voltage[step] =
            V0 - constantVoltage.current[step] * R;
    }

    // Print the voltage and current for constant current circuit
    cout << "Constant Current Capacitor:" << endl;
    cout << "Time (s)\tVoltage (V)\tCurrent (A)" << endl;

    // Print every 200 timesteps
    for (int step = 0; step <= steps; step += 200)
    {
        cout << constantCurrent.time[step] << "\t"
             << constantCurrent.voltage[step] << "\t"
             << constantCurrent.current[step] << endl;
    }

    cout << endl;

    // Print the voltage and current for constant voltage circuit
    cout << "Constant Voltage Capacitor:" << endl;
    cout << "Time (s)\tVoltage (V)\tCurrent (A)" << endl;

    // Print every 200 timesteps
    for (int step = 0; step <= steps; step += 200)
    {
        cout << constantVoltage.time[step] << "\t"
             << constantVoltage.voltage[step] << "\t"
             << constantVoltage.current[step] << endl;
    }

    // Free allocated memory for constantCurrent
    delete[] constantCurrent.time;
    delete[] constantCurrent.voltage;
    delete[] constantCurrent.current;

    // Free allocated memory for constantVoltage
    delete[] constantVoltage.time;
    delete[] constantVoltage.voltage;
    delete[] constantVoltage.current;

    return 0;
}
