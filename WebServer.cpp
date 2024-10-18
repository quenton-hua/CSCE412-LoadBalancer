#include "WebServer.h"
#include "LoadBalancer.h"
#include <iostream>
#include <fstream> // For file logging

WebServer::WebServer() {
    is_busy = false;
    time_left = 0;
    start_time = 0;
}

bool WebServer::isAvailable() {
    return !is_busy;
}

void WebServer::processRequest(const Request& req, int current_time) {
    current_request = req;
    time_left = req.process_time;
    is_busy = true;
    start_time = current_time;  // Record when the server starts processing
}

void WebServer::tick(int current_time, LoadBalancer* load_balancer) {
    if (is_busy) {
        --time_left;
        if (time_left <= 0) {
            is_busy = false;
            
            // Log the response time for the completed request
            int processing_time = current_time - start_time;
            std::ofstream log_file("metrics_log.txt", std::ios_base::app);  // Open in append mode
            log_file << "Request processed in " << processing_time << " units of time." << std::endl;
            log_file.close();

            // Increment total processed requests
            load_balancer->total_processed_requests++;
        }
    }
}
