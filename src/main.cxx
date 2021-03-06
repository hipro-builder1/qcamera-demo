#include <QApplication>

#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include "app.h"

int main(int argc, char *argv[]) {
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
  spdlog::init_thread_pool(8192, 1);

  // Logger for the application-thread
  auto at_logger = std::make_shared<spdlog::async_logger>(
      "camera_demo_window", console_sink, spdlog::thread_pool(),
      spdlog::async_overflow_policy::block);

  spdlog::register_logger(at_logger);
  spdlog::set_level(spdlog::level::trace);

  QApplication app(argc, argv);

  auto window = new CameraDemoWindow(at_logger);
  window->show();

  return app.exec();
}