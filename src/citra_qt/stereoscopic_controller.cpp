#include <QBoxLayout>
#include <QRadioButton>

#include "citra_qt/stereoscopic_controller.h"
#include "citra_qt/util/util.h"

#include "core/core.h"

StereoscopicControllerWidget::StereoscopicControllerWidget(QWidget* parent)
    : QDockWidget(tr("Stereoscopic Controller"), parent) {
    setObjectName("StereoscopicControllerWidget");
    slider = new QSlider();
    connect(slider, SIGNAL(sliderMoved(int)), SLOT(OnSliderMoved(int)));
    QRadioButton* buttonLeftOnly = new QRadioButton(tr("Left eye only"));
    QRadioButton* buttonRightOnly = new QRadioButton(tr("Right eye only"));
    QRadioButton* buttonAnaglyph = new QRadioButton(tr("Anaglyph"));
    QRadioButton* buttonOff = new QRadioButton(tr("Off"));
    connect(buttonLeftOnly, &QRadioButton::clicked,
            [=]() { emit StereoscopeModeChanged(EmuWindow::StereoscopicMode::LeftOnly); });
    connect(buttonRightOnly, &QRadioButton::clicked,
            [=]() { emit StereoscopeModeChanged(EmuWindow::StereoscopicMode::RightOnly); });
    connect(buttonAnaglyph, &QRadioButton::clicked,
            [=]() { emit StereoscopeModeChanged(EmuWindow::StereoscopicMode::Anaglyph); });
    connect(buttonOff, &QRadioButton::clicked,
            [=]() { emit StereoscopeModeChanged(EmuWindow::StereoscopicMode::Off); });
    buttonOff->setChecked(true);
    emit StereoscopeModeChanged(EmuWindow::StereoscopicMode::Anaglyph);
    QVBoxLayout* subLayuout = new QVBoxLayout();
    subLayuout->addWidget(buttonLeftOnly);
    subLayuout->addWidget(buttonRightOnly);
    subLayuout->addWidget(buttonAnaglyph);
    subLayuout->addWidget(buttonOff);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(slider);
    layout->addLayout(subLayuout);
    QWidget* w = new QWidget(this);
    w->setLayout(layout);
    setWidget(w);
    setEnabled(false);
}
void StereoscopicControllerWidget::OnSliderMoved(int value) {
    float fv = (float)(value - slider->minimum()) / (slider->maximum() - slider->minimum());
    emit DepthChanged(fv);
}

void StereoscopicControllerWidget::OnEmulationStarting(EmuThread* emu_thread) {
    setEnabled(true);
}

void StereoscopicControllerWidget::OnEmulationStopping() {
    setEnabled(false);
}