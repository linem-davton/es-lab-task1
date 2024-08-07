/**
 * @file server.h
 * @brief Header file for the CommServer class.
 *
 * This file declares the CommServer class, which implements a communication
 * server for interacting with the inverted pendulum simulation. It utilizes
 * Boost.Asio for asynchronous I/O operations and Boost.Beast for handling HTTP
 * requests and responses. The CommServer class facilitates communication with
 * the simulation, allowing control and monitoring of simulation parameters over
 * network.
 *
 * @author Utkarsh Raj
 * @date 10-April-2024
 */

#include "boost/asio/ip/tcp.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/config.hpp>
#include <iostream>
#include <json.hpp>

#include "controller.h"
#include "simulator.h"
#include <mutex>
#include <thread>

using json = nlohmann::json;

namespace beast = boost::beast;   // from <boost/beast.hpp>
namespace http = beast::http;     // from <boost/beast/http.hpp>
namespace net = boost::asio;      // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

/**
 * @brief Class for managing communication frontend and simulation backend.
 *
 * The CommServer class implements a communication server that handles HTTP
 * requests to control and monitor the inverted pendulum simulation. It listens
 * for incoming connections, processes HTTP requests, and sends corresponding
 * responses.
 */
class CommServer {
  Simulator &sim; ///< Reference to the simulator object

  net::io_context ioc{1}; ///< io context required for all I/O

  net::ip::address address{
      net::ip::make_address("0.0.0.0")}; ///< Binds on all interfaces
  unsigned short port{8000};             ///< Server Port
  tcp::acceptor
      acceptor; ///< The acceptor is used to listen for incoming connections
public:
  /**
   * @brief Constructor for CommServer.
   *
   * Initializes the CommServer with the specified simulator object and listens
   * for incoming connections on the specified IP address and port.
   *
   * @param sim Reference to the simulator object.
   */
  CommServer(Simulator &sim) : sim(sim), acceptor(ioc, {address, port}) {}
  /**
   * @brief Starts the communication server.
   *
   * This method starts the communication server in a separate thread.
   */

  void start_server();

private:
  /**
   * @brief Runs the communication server loop.
   *
   * This method continuously listens for incoming connections, accepts
   * them, and handles HTTP requests.
   */
  void run_server();
  /**
   * @brief Handles an incoming HTTP request.
   *
   * This method reads an HTTP request from the given socket, processes
   * it, and sends an appropriate HTTP response.
   *
   * @param socket The socket for communicating with the client.
   */
  void handle_request(tcp::socket &socket);
};
