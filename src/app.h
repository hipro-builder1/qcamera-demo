#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "spdlog/spdlog.h"

class CameraDemoWindow : public QDialog {
  Q_OBJECT

public:
  CameraDemoWindow(std::shared_ptr<spdlog::logger> logger);

  void start();

private:
  void onCaptureClicked();
  void onModeClicked();

private:
  std::shared_ptr<spdlog::logger> m_logger;

  QCamera *m_current_camera = nullptr;
  QCameraViewfinder *m_cvf = nullptr;
  QVBoxLayout *m_main_layout = nullptr;
  QHBoxLayout *m_button_layout = nullptr;
  QPushButton *m_pb_change_mode = nullptr;
  QPushButton *m_pb_capture = nullptr;
  QLabel *m_lbl_camera_mode = nullptr;
  QCameraImageCapture *m_img_capture = nullptr;
};