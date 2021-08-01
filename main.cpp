#include "mainwindow.h"
#include <QApplication>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/face/facerec.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <QDebug>
#include <QTextCodec>

using namespace std;
using namespace cv;
using namespace cv::face;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


