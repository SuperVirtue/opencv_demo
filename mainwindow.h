#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTimer"
#include "QImage"

#include "opencv2/opencv.hpp"
#include "mysqlquerymodel.h"

#include <QSql>
#include <QDir>
#include <QAction>
#include <QDateTime>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    bool isDirExist(QString fullPath);

    void clearEmpolyeeInformation();

    ~MainWindow();

    QSqlDatabase dbconn;

private slots:

    void ReadFrame_1();

    void ReadFrame_2();

    void OpenCameraClicked();

    void CloseCameraClicked();

    void FaceStorageClicked();

    void InformationSeveClicked();

    void OpenSecondaryCamera();

    void queryButtonClicked();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture capture;

    cv::CascadeClassifier cascada;

    QTimer *timer_1,*timer_2;
    cv::Mat frame,frame_gray;
    int pic_num;
    std::vector<cv::Rect> faces;
    std::vector<cv::Rect> faces_2;

    QString hostName;
    QString dbName;
    QString userName;
    QString password;


    QStringList List_name,List_number;
    QVector<QDateTime> employee_last_attendance_time;

    QDateTime current_time ;
    QString str="";//记录名字
    QString last_query="";
};

#endif // MAINWINDOW_H
