#include <boost/asio/io_context.hpp>
#include <sdbusplus/bus.hpp>
#include <sdbusplus/asio/connection.hpp>
#include <sdbusplus/asio/object_server.hpp>

int main(int argc, char* argv[]) {
  boost::asio::io_context io;
  auto systemBus = std::make_shared<sdbusplus::asio::connection>(io);
  systemBus->request_name("xyz.openbmc_project.BU6Test");
  // Create the D-Bus object
  sdbusplus::asio::object_server objectServer(systemBus);
  auto intf = objectServer.add_interface("/xyz/openbmc_project/inventec/BU6",
    "xyz.openbmc_project.inventec.Test");
  intf->initialize();
  io.run();
  return 0;
}
