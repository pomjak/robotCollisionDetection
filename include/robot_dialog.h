#include "robot.h"
#include "ui_robot-properties-dialog.h"
#include <QObject>

class RobotPropertiesDialog
    : public QDialog
    , private Ui::PropertiesDialog
{
    Q_OBJECT

  public:
    RobotPropertiesDialog(Robot *r, QWidget *parent = 0);

  private slots:
    void on_buttonBox_accepted();

  private:
    Robot *m_robot;
};
