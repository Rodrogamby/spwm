#include <bits/stdc++.h>

using namespace std;

int main()
{
    double levels, m; cin >> levels >> m;
    levels = (int) levels;

    const double PERIOD_TICKS = 1600;

    const double time_delta = 1 / levels;

    vector<vector<int>> table(3, vector<int>(levels, 0));

    double time = 0;
    for(int j = 0; j < 3; j++)
    {
	for(int i = 0; i < levels; i++)
	{
	    table[j][i] = (m * PERIOD_TICKS / 2)* sin(2*M_PI*1*time + j*2*M_PI/3) + PERIOD_TICKS / 2;
	    time += time_delta;
	}
    }

    // Print out lookup table as array
    for(int j = 0; j < 3; j++)
    {
	printf("{ %d", table[j][0]);
	for(int i = 1; i < levels; i++) // i was 1
	{
	    printf(", %d", table[j][i]);
	}
	printf(" }\n");
    }

    /*
    //Print timer 6 (modulator signal) period in ticks i.e. pwm duty cycle update interval
    //
    double timer_clock_frequency = 32000000;
    double prescaler = 64;
    double sine_fr equency = 100.0;
    double real_time_delta = (1.0 / (2.0 * sine_frequency)) / levels; // it should update every half period / levels

    double timer_period = real_time_delta / (prescaler / timer_clock_frequency);
    int error = timer_period - (int) timer_period;
    printf("\n--[ Timer Calculator ]--\nTimer clock speed: %dHz\nPrescaler: %d (-1)\nModulator frequency: %dHz\n===\nTimer period (ticks): %f\nTime equivalent: %fs\n", \
	   (int)timer_clock_frequency, (int)prescaler, (int)sine_frequency, timer_period, real_time_delta);
*/
    return 0;
}
