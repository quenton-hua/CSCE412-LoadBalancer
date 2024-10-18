#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "WebServer.h"
#include <queue>
#include <vector>

/**
 * @brief Class that manages web servers and request queue.
 */
class LoadBalancer {
private:
    std::queue<Request> requestqueue;     ///< Queue of requests to be processed.
    std::vector<WebServer*> web_servers;  ///< List of web servers managed by the load balancer.
    int total_time;                       ///< Total time for simulation.
    int current_time;                     ///< Current time in the simulation.
    
public:
    int total_processed_requests;         ///< Total number of requests processed.

    /**
     * @brief Construct a new LoadBalancer object.
     * 
     * @param initial_servers The initial number of web servers to start with.
     * @param total_time The total time for which the load balancer will run.
     */
    LoadBalancer(int initial_servers, int total_time);

    /**
     * @brief Distribute requests to available web servers.
     */
    void distributeRequests();

    /**
     * @brief Simulate one time unit of the load balancer.
     */
    void tick();

    /**
     * @brief Add a new request to the queue.
     */
    void addRequest();

    /**
     * @brief Dynamically allocate or deallocate servers based on load.
     */
    void scaleServers();

    /**
     * @brief Run the load balancer for the specified total time.
     */
    void run();

    /**
     * @brief Print total processed requests.
     */
    void printProcessedRequests();
};

#endif
