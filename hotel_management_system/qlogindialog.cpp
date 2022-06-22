#include "qlogindialog.h"
#include <QPainter>
#include <QTime>
#include <QMessageBox>

#include "managerservice.h"
#include <QDebug>

QLoginDialog::QLoginDialog(QWidget* parent) : QDialog(parent, Qt::WindowCloseButtonHint),
    UserLabel(this), PwdLabel(this), CaptLabel(this),
    UserEdit(this), PwdEdit(this), CaptEdit(this),
    LoginBtn(this), CancelBtn(this),
    m_vf(NULL)
{
    UserLabel.setText("User name:");
    UserLabel.move(20, 30);
    UserLabel.resize(85, 25);

    UserEdit.move(110, 30);
    UserEdit.resize(180, 25);

    PwdLabel.setText("Password:");
    PwdLabel.move(20, 65);
    PwdLabel.resize(85,25);

    PwdEdit.move(110, 65);
    PwdEdit.resize(180, 25);
    PwdEdit.setEchoMode(QLineEdit::Password);

    CaptLabel.setText("Check code:");
    CaptLabel.move(20, 100);
    CaptLabel.resize(85, 25);

    CaptEdit.move(110, 100);
    CaptEdit.resize(65, 25);

    CancelBtn.setText("Cancel");
    CancelBtn.move(110, 145);
    CancelBtn.resize(85, 30);

    LoginBtn.setText("Log in");
    LoginBtn.move(205, 145);
    LoginBtn.resize(85, 30);

    m_timer.setParent(this);

    setWindowTitle("Log in");
    setFixedSize(310, 205);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(Timer_Timeout()));
    connect(&LoginBtn, SIGNAL(clicked()), this, SLOT(LoginBtn_Clicked()));
    connect(&CancelBtn, SIGNAL(clicked()), this, SLOT(CancelBtn_Clicked()));

    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());

    m_timer.start(100);
}

void QLoginDialog::LoginBtn_Clicked()
{
    QString captcha = CaptEdit.text().replace(" ", "");

    if( m_captcha.toLower() == captcha.toLower() )
    {
        m_user = UserEdit.text().trimmed();
        m_pwd = PwdEdit.text();

        if( m_user == "" )
        {
            QMessageBox::information(this, "Message", "User name cannot be null!");
        }
        else if( m_pwd == "" )
        {
            QMessageBox::information(this, "Message", "Password cannot be null!");
        }
        else if( (m_vf != NULL) && !m_vf(m_user) )
        {
            QMessageBox::critical(this, "Error", "User name is illegal, please re-enter it!");
        }
        else
        {
            QList<manager> managers = managerService::selectManagerByID(m_user);
            if (managers.size() == 0)
            {
                QMessageBox::critical(this, "Error", "The user name doesn't exist.");
                m_captcha = getCaptcha();
                CaptEdit.selectAll();
                return;
            }
            if (!(QString::number(managers[0].getManager_id()) == m_user && managers[0].getManager_password() == m_pwd))
            {
                QMessageBox::critical(this, "Error", "User name and password don't match.");
                m_captcha = getCaptcha();
                CaptEdit.selectAll();
                return;
            }
            else{
                hide();
                m_MainWin.setManagerName(managers[0].getManager_name());
                m_MainWin.setManagerAuthority(managers[0].getManager_authority());
                m_MainWin.getManagerID(QString::number(managers[0].getManager_id()));
                m_MainWin.init_Model();
                m_MainWin.updateManageBtn();
                m_MainWin.show();
                accept();
            }
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Check number input error!");

        m_captcha = getCaptcha();

        CaptEdit.selectAll();
    }
}

void QLoginDialog::CancelBtn_Clicked()
{
    done(Rejected);
}

QString QLoginDialog::getUser()
{
    return m_user;
}

QString QLoginDialog::getPwd()
{
    return m_pwd;
}

QWidget *QLoginDialog::getWidget()
{
    return &m_MainWin;
}

void QLoginDialog::Timer_Timeout()
{
    m_colors = getColors();

    update();
}

void QLoginDialog::showEvent(QShowEvent* event)
{
    m_captcha = getCaptcha();
    m_colors = getColors();

    QDialog::showEvent(event);
}

void QLoginDialog::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.fillRect(180, 100, 84, 24, Qt::white);

    painter.setFont(QFont("Comic Sans MS", 12));

    for(int i=0; i<150; i++)
    {
        painter.setPen(m_colors[i%4]);
        painter.drawPoint(180 + qrand() % 84, 100 + qrand() % 24);
    }

    for(int i=0; i<4; i++)
    {
        painter.setPen(m_colors[i]);
        painter.drawText(180 + 20 * i, 100, 20, 24, Qt::AlignCenter, QString(m_captcha[i]));
    }

    QDialog::paintEvent(event);
}

QString QLoginDialog::getCaptcha()
{
    QString ret = "";

    for(int i=0; i<4; i++)
    {
        int c = (qrand() % 2) ? 'a' : 'A';

        ret += static_cast<QChar>(c + qrand() % 26);
    }

    return ret;
}

Qt::GlobalColor* QLoginDialog::getColors()
{
    static Qt::GlobalColor colors[4];

    for(int i=0; i<4; i++)
    {
        colors[i] = static_cast<Qt::GlobalColor>(2 + qrand() % 16);
    }

    return colors;
}

void QLoginDialog::setValFunc(ValFunc vf)
{
    m_vf = vf;
}

QLoginDialog::~QLoginDialog()
{

}


