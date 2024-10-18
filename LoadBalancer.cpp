#include "LoadBalancer.h"
#include <iostream>
#include <chrono>
#include <fstream> // For file logging

LoadBalancer::LoadBalancer(int initial_servers, int time)
    : total_time(time), current_time(0), total_processed_requests(0) {
    // Initialize the starting number of web servers
    for (int i = 0; i < initial_servers; ++i) {
        web_servers.push_back(new WebServer());
    }

    // Fill the initial request queue
    for (int i = 0; i < initial_servers * 100; ++i) {
        requestqueue.push(Request());
    }
}


void LoadBalancer::scaleServers() {
    // Dynamically allocate servers as needed
    if (requestqueue.size() > web_servers.size() * 2) {
        web_servers.push_back(new WebServer());  // Add new server if needed
        std::cout << "Added a new server!" << std::endl;
    } else if (requestqueue.empty() && web_servers.size() > 1) {
        delete web_servers.back();
        web_servers.pop_back();  // Remove a server if not needed
        std::cout << "Removed a server!" << std::endl;
    }
}

void LoadBalancer::printProcessedRequests() {
    std::cout << "Total requests processed: " << total_processed_requests << std::endl;
}

void LoadBalancer::distributeRequests() {
    for (WebServer* server : web_servers) {
        if (server->isAvailable() && !requestqueue.empty()) {
            server->processRequest(requestqueue.front(), current_time);  // Pass current time
            requestqueue.pop();
        }
    }
}

void LoadBalancer::tick() {
    for (WebServer* server : web_servers) {
        server->tick(current_time, this);  // Pass the LoadBalancer object to tick
    }
    current_time++;
}

void LoadBalancer::addRequest() {
    // Simulate adding new requests at random intervals
    if (rand() % 10 == 0) {
        requestqueue.push(Request());
    }
}


void LoadBalancer::run() {
    // Open a file to log metrics
    std::ofstream log_file("log.txt");
    if (!log_file.is_open()) {
        std::cerr << "Error: Could not open log file!" << std::endl;
        return;
    }

    // Capture the start time
    auto start_time = std::chrono::high_resolution_clock::now();

    // Simulation loop
    while (current_time < total_time) {
        distributeRequests();
        tick();
        addRequest();
        scaleServers();

        // Calculate server utilization
        int busy_servers = 0;
        for (const auto& server : web_servers) {
            if (!server->isAvailable()) busy_servers++;
        }
        double utilization = (double)busy_servers / web_servers.size() * 100;

        // Log metrics at each time step
        log_file << "Time: " << current_time 
                 << ", Queue Size: " << requestqueue.size()
                 << ", Servers: " << web_servers.size()
                 << ", Busy Servers: " << busy_servers
                 << ", Utilization: " << utilization << "%"
                 << ", Requests Processed: " << total_processed_requests << std::endl;

        std::cout << "Time: " << current_time << ", Queue Size: " 
                  << requestqueue.size() << ", Servers: " << web_servers.size() << std::endl;

        current_time++;
    }

    // Capture the end time
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    // Log total execution time and requests processed
    log_file << "Total execution time: " << elapsed.count() << " seconds." << std::endl;
    log_file << "Total requests processed: " << total_processed_requests << std::endl;

    // Close the log file
    log_file.close();

    // Print the total execution time to the console
    std::cout << "Total execution time: " << elapsed.count() << " seconds." << std::endl;

    // Print the total number of processed requests to the console
    printProcessedRequests();
}
