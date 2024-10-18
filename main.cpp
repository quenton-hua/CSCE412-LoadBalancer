#include "LoadBalancer.h"
#include <iostream>

int main() {
    int num_servers, simulation_time;

    // User input for the starting number of servers and simulation time
    std::cout << "Enter the starting number of web servers: ";
    std::cin >> num_servers;
    std::cout << "Enter the simulation time: ";
    std::cin >> simulation_time;

    // Initialize the load balancer with the starting number of servers
    LoadBalancer lb(num_servers, simulation_time);

    // Run the simulation
    lb.run();

    return 0;
}
