#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
class LoadBalancer;  // Forward declaration to avoid circular dependency

/**
 * @brief Class representing a web server that processes requests.
 * 
 * The WebServer class handles requests assigned by the load balancer. It tracks 
 * whether the server is busy, how much time is left to complete the current request, 
 * and when the request started.
 */
class WebServer {
private:
    bool is_busy;         ///< Flag indicating if the server is currently processing a request.
    Request current_request;  ///< The request currently being processed by the server.
    int time_left;        ///< The remaining time to finish processing the current request.
    int start_time;       ///< The time when the server started processing the current request.

public:
    /**
     * @brief Construct a new WebServer object.
     */
    WebServer();

    /**
     * @brief Check if the server is available to process a new request.
     * 
     * This method checks if the server is currently processing a request.
     * 
     * @return true If the server is available (not busy).
     * @return false If the server is currently busy with a request.
     */
    bool isAvailable();

    /**
     * @brief Start processing a new request.
     * 
     * This method assigns a new request to the server and records the time it 
     * was assigned. The request will take a specified amount of time to complete.
     * 
     * @param req The request to be processed.
     * @param current_time The current time in the simulation when the request is assigned.
     */
    void processRequest(const Request& req, int current_time);

    /**
     * @brief Simulate the passage of time by decrementing the time left to process the request.
     * 
     * This method simulates the progression of time in the system by reducing the 
     * remaining time for the current request. If the request completes, the server 
     * becomes available for new requests.
     * 
     * @param current_time The current time step in the simulation.
     * @param load_balancer The load balancer managing the servers.
     */
    void tick(int current_time, LoadBalancer* load_balancer);
};

#endif
