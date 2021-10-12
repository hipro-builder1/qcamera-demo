#include <QCameraInfo>

#include "app.h"

CameraDemoWindow::CameraDemoWindow(std::shared_ptr<spdlog::logger> logger)
    : m_logger(logger) {
  setWindowTitle("Demo Window");
  setMaximumSize(QSize(800, 600));
  setMinimumSize(QSize(800, 600));

  m_current_camera = new QCamera(QCameraInfo::availableCameras().first());
  m_cvf = new QCameraViewfinder();
  m_current_camera->setViewfinder(m_cvf);

  m_pb_change_mode = new QPushButton("Mode");
  m_pb_capture = new QPushButton("Capture");
  auto capture_mode = m_current_camera->captureMode();
  m_lbl_camera_mode = new QLabel(capture_mode == 0 ? "ViewFinder" : "Media");

  m_main_layout = new QVBoxLayout(this);
  m_main_layout->setSizeConstraint(QLayout::SetMaximumSize);
  m_main_layout->addWidget(m_cvf);

  m_button_layout = new QHBoxLayout(this);
  m_button_layout->setSizeConstraint(QLayout::SetMaximumSize);
  m_button_layout->addWidget(m_pb_change_mode);
  m_button_layout->addWidget(m_lbl_camera_mode);
  m_button_layout->addWidget(m_pb_capture);

  m_main_layout->addLayout(m_button_layout);

  connect(m_pb_capture, &QPushButton::clicked, this,
          &CameraDemoWindow::onCaptureClicked);
  connect(m_pb_change_mode, &QPushButton::clicked, this,
          &CameraDemoWindow::onModeClicked);

  m_cvf->show();
  m_current_camera->start();
  setLayout(m_main_layout);
}

void CameraDemoWindow::onCaptureClicked() {
  m_img_capture = new QCameraImageCapture(m_current_camera);
  m_img_capture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
  m_img_capture->setObjectName("test.jpg");
  m_current_camera->setCaptureMode(QCamera::CaptureStillImage);
  m_img_capture->capture();
}

void CameraDemoWindow::onModeClicked() {
  auto capture_mode = m_current_camera->captureMode();
  if (capture_mode == QCamera::CaptureStillImage) {
    m_current_camera->setCaptureMode(QCamera::CaptureVideo);
  } else {
    m_current_camera->setCaptureMode(QCamera::CaptureStillImage);
  }
}
