// main.cpp

#include <QApplication>
#include<iostream>
#include <QDesktopWidget>
#include<vector>
#include <QFileDialog>
#include <QDebug>
#include "window.h"
#include "main5cpp.h"
#include<main_choice.h>
extern char *files;
QString s="";
class QFileDialogTester : public QWidget
{
public:
  QString openFile()
  {
    QString filename =  QFileDialog::getOpenFileName(
          this,
          "Open Document",
          QDir::currentPath(),
          "All files (*.*)");

    if( !filename.isNull() )
    {
      qDebug() << "selected file path : " << filename.toUtf8();
    }
    return filename;
  }
};
QString retstr()
{
    qDebug() << "selected file path : ";
    return s;
}
int main(int argc, char *argv[])
{


    QApplication app(argc, argv);


    main_choice d;
    d.setModal(true);
    d.exec();

//    QFileDialogTester test;
//    QString s;
//    s=test.openFile();
//    QFile file(s);
    //s.toLatin1().data();
  //  qDebug() << "kbxrh : " << (s.mid(s.lastIndexOf("/")+1).toLatin1().data());
                //file.fileName().toLatin1().data();
    //files= (s.mid(s.lastIndexOf("/")+1).toLatin1().data());
    //qDebug() << "kbxrh : " <<files;
    //////////////////////
    if(true){
    Window window;
    window.resize(window.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = window.width() * window.height();

    window.setWindowTitle("OpenGL with Qt");

    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.show();
    else
        window.showMaximized();
    app.exec();
    }
    else{}
}
