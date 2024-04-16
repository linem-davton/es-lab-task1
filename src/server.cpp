/**
 * @file server.cpp
 * @brief Implementation file for the CommServer class.
 *
 * This file contains the implementation of the methods declared in the server.h
 * header file. It provides the functionality for handling incoming HTTP
 * requests and managing communication with the inverted pendulum simulation.
 *
 * @author Utkarsh Raj
 * @date 10-April-2024
 */

#include "server.h"

void CommServer::start_server() {
  std::thread comm_thread(&CommServer::run_server, this);
  comm_thread.join();
}

void CommServer::run_server() {

  while (true) {
    // receive new connection
    tcp::socket socket(ioc);
    // block until we get a connection
    acceptor.accept(socket);
    handle_request(socket);
  }
}

void CommServer::handle_request(tcp::socket &socket) {

  beast::flat_buffer buffer;
  http::request<http::string_body> req;
  http::read(socket, buffer, req);

  if (req.method() == http::verb::get) {
    json j;
    {
      j["time"] = std::round(sim.T * 100) / 100;
      j["x"] = std::round(sim.x[0] * 100) / 100;
      j["theta"] = sim.theta[sim.i];
      j["x_dot"] = sim.x_dot[0];
      j["theta_dot"] = sim.theta_dot[0];
      j["x_dot_dot"] = sim.x_dot_dot[0];
      j["theta_dot_dot"] = sim.theta_dot_dot[0];
      j["force"] = sim.F;
      j["energy"] = sim.E;
      j["pause"] = sim.g_pause.load();
    }
    std::string response = j.dump();
    if (req.target() == "/sim") {
      http::response<http::string_body> res{http::status::ok, req.version()};
      res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
      res.set(http::field::content_type, "application/json");

      res.set(boost::beast::http::field::access_control_allow_origin,
              "*"); // Adjust origin as needed
      res.set(boost::beast::http::field::access_control_allow_methods,
              "GET, POST, OPTIONS"); // Include if needed

      res.keep_alive(req.keep_alive());
      res.body() = response;
      res.prepare_payload();
      http::write(socket, res);
      return;
    }
    if (req.target() == "/status") {
      json status;
      status["pause"] = sim.g_pause.load();
      status["start"] = sim.g_start.load();
      std::string status_response = status.dump();
      http::response<http::string_body> res{http::status::ok, req.version()};
      res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
      res.set(http::field::content_type, "application/json");

      res.set(boost::beast::http::field::access_control_allow_origin,
              "*"); // Adjust origin as needed
      res.set(boost::beast::http::field::access_control_allow_methods,
              "GET, POST, OPTIONS"); // Include if needed

      res.keep_alive(req.keep_alive());
      res.body() = status_response;
      res.prepare_payload();
      http::write(socket, res);
    }
  }
  if (req.method() == http::verb::post) {
    if (req.target() == "/pid") {
      json pid = json::parse(req.body());
      std::lock_guard<std::mutex> lock(sim.g_start_mutex);
      sim.m_controller->update_params(pid["kp"], pid["ki"], pid["kd"]);
    }
    if (req.target() == "/reset") {
      std::lock_guard<std::mutex> lock(sim.g_start_mutex);
      sim.reset_simulator();
    }
    if (req.target() == "/startstop") {
      if (!sim.g_start) {
        std::lock_guard<std::mutex> start_lock(sim.g_start_mutex);
        sim.g_start = true;
        sim.g_start_cv.notify_one();
      }
      std::lock_guard<std::mutex> lock(sim.g_pause_mutex);
      sim.g_pause = !sim.g_pause;
      sim.g_pause_cv.notify_one();
    }
    if (req.target() == "/params") {
      json params = json::parse(req.body());
      std::lock_guard<std::mutex> lock(sim.g_start_mutex);
      sim.update_params(params["ref"], params["delay"], params["jitter"]);
    }
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/plain");

    res.set(boost::beast::http::field::access_control_allow_origin,
            "*"); // Adjust origin as needed
    res.set(boost::beast::http::field::access_control_allow_methods,
            "GET, POST, OPTIONS"); // Include if needed

    res.keep_alive(req.keep_alive());
    res.body() = "Accepted";
    res.prepare_payload();
    http::write(socket, res);
    return;
  }
  if (req.method() == http::verb::options) {
    // std::cout << "OPTIONS request received\n";
    http::response<http::empty_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::access_control_allow_origin,
            "*"); // Specific origin
    res.set(http::field::access_control_allow_methods,
            "GET, POST, OPTIONS"); // Include all needed methods
    res.set(http::field::access_control_allow_headers, "Content-Type");
    res.keep_alive(req.keep_alive());
    http::write(socket, res);
    return;

  } else {
    http::response<http::string_body> res{http::status::bad_request,
                                          req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = "Invalid request-target";
    res.prepare_payload();
    http::write(socket, res);
    return;
  }
}
