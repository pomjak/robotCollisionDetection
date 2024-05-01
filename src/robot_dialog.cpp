#include "robot_dialog.h"

RobotPropertiesDialog::RobotPropertiesDialog(Robot *r, QWidget *parent)
    : m_robot(r)
    , QDialog(parent)

{
    setupUi(this);

    posXBox->setValue(m_robot->x());
    posYBox->setValue(m_robot->y());
    orientationBox->setValue(m_robot->angle());
    rotationBox->setValue(m_robot->rotateBy());
    detectDistanceBox->setValue(m_robot->detectionDistance());
    speedBox->setValue(m_robot->speed());
    // ! TODO directionComboBox
}

void RobotPropertiesDialog::on_buttonBox_accepted()
{
    m_robot->setPos(posXBox->value(), posYBox->value());
    m_robot->setAngle(orientationBox->value());
    m_robot->setSpeed(speedBox->value());
    m_robot->setRotateBy(rotationBox->value());
    m_robot->update();
    QDialog::accept();
}
