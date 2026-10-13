#include <iostream>

using namespace std;

struct _capacitor // holds the data for a capacitor
{
    double* time; // pointer to the time
    double* voltage; //pointer to the voltage
    double* current; //pointer to the current
    double C;  // capacitance in farads

};

typedef struct _capacitor Capacitor;

int main()
{
    const int Steps = 50000; // Number of time steps
    const double dt = 1e-10; // Time step in seconds
    const double R = 1000.0; //Resistance in OHMS
    const double V0 = 10.0; // Supply voltage in volts
    const double C = 100e-12; // Capacitance in farads
    const double I0 = 1e-2; // Constant current in amps

    Capacitor constantCurrent;
    Capacitor constantVoltage;
    
    constantCurrent.C = C;
    constantVoltage.C = C;

    //Allocate the arrays (Step + 1 elements for the initial condition)
    constantCurrent.time = new double[steps + 1];
    constantCurrent.voltage = new double[steps + 1];
    constantCurrent.current = new double[steps + 1]; 

    constantVoltage.time = new double[steps + 1];
    constantVoltage.voltage = new double[steps + 1];
    constantVoltage.current = new double[steps + 1];

    // Initial conditions for the capacitors
    constantCurrent.time[0] = 0.0;
    constantCurrent.voltage[0] = 0.0;
    constantCurrent.current[0] = I0;

    // Initial conditions for the constant voltage capacitor
    constantVoltage.time[0] = 0.0;
    constantVoltage.voltage[0] = 0.0;
    constantVoltage.current[0] = V0/R;

    for (int step = 1; step <= Steps; step++)
    {
        constantCurrent.time[step] = constantCurrent.time[step - 1] + dt;
        constantCurrent.voltage[step] = constantCurrent.voltage[step - 1] + constantCurrent.current[step - 1] * dt / constantCurrent.C;
        constantCurrent.current[step] = I0;

        constantVoltage.time[step] = constantVoltage.time[step - 1] * dt;
        constantVoltage.voltage[step] = V0;
        constantVoltage.current[step] = (V0 - constantVoltage.voltage[step - 1]) / R;


    }


}