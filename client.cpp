#include <boost/asio/io_context.hpp>
#include <sdbusplus/bus.hpp>
#include <sdbusplus/asio/connection.hpp>
#include <sdbusplus/asio/object_server.hpp>
#include <iostream>

static constexpr std::string_view demoDbusName = "xyz.openbmc_project.BU6Test";
static constexpr std::string_view demoPath = "/xyz/openbmc_project/inventec/BU6";
static constexpr std::string_view propertiesIntf = "org.freedesktop.DBus.Properties";
static constexpr std::string_view demoIntf = "xyz.openbmc_project.inventec.SW2A";



int main(int argc, char* argv[]) {
  boost::asio::io_context io;
  auto systemBus = std::make_shared<sdbusplus::asio::connection>(io);
  //auto systemBus = sdbusplus::bus::new_default_system();
  try{
      auto methodCall = systemBus->new_method_call( demoDbusName.data(), demoPath.data(), propertiesIntf.data(), "Get");
      methodCall.append(demoIntf.data(), "Job_Number");
      auto reply = systemBus->call(methodCall);
      std::variant<std::string> value;
      reply.read(value);
      std::cout << "Job_Number: " << std::get<std::string>(value) << std::endl;
  } catch (const std::exception& e)
  {
      std::cerr << "Error: " << e.what() << std::endl;
  }
  io.run();
  return 0;
}
