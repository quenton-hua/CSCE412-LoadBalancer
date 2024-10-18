#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
class LoadBalancer;  // Forward declaration to avoid circular dependency

/**
 * @brief Class representing a web server that processes requests.
 */
class WebServer {
private:
    bool is_busy;         ///< Is the server currently processing a request?
    Request current_request;  ///< The current request being processed by the server.
    int time_left;        ///< The remaining time to finish processing the current request.
    int start_time;       ///< The time at which the server started processing the request.

public:
    /**
     * @brief Construct a new WebServer object.
     */
    WebServer();

    /**
     * @brief Check if the server is available to process a new request.
     * 
     * @return true If the server is available.
     * @return false If the server is busy.
     */
    bool isAvailable();

    /**
     * @brief Start processing a new request.
     * 
     * @param req The request to be processed.
     * @param current_time The current time when the request is assigned.
     */
    void processRequest(const Request& req, int current_time);

    /**
     * @brief Simulate the passage of time by decrementing the time left to process the request.
     * 
     * @param current_time The current time step in the simulation.
     * @param load_balancer The load balancer managing the servers.
     */
    void tick(int current_time, LoadBalancer* load_balancer);
};

#endif
