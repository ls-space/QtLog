#include "spdLoger.h"

#include "include/spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"

#include <QApplication>
#include <QDir>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>

SpdLoger::SpdLoger(QObject *parent) : QObject(parent)
{
    iniSpdLoger();
    QFuture<void> future = QtConcurrent::run(cleanOldData);
}

SpdLoger::~SpdLoger()
{
    spdlog::drop_all();//clean all logger
}

void SpdLoger::handleLog(QString logInfo, int logLevel, int logPlace)
{
    auto rotatingLogger = spdlog::get(mRotatingLogger);
    auto dailylogger = spdlog::get(mDailyLogger);

    //0-debug,1-info,2-warn,3-error
    switch (logLevel) {
    case 0:{
        if(logPlace==0)
            rotatingLogger->debug(logInfo.toStdString());
        else if(logPlace==1)
            dailylogger->debug(logInfo.toStdString());
        else if(logPlace==2){
            rotatingLogger->debug(logInfo.toStdString());
            dailylogger->debug(logInfo.toStdString());
        }
    }break;
    case 1:{
        if(logPlace==0)
            rotatingLogger->info(logInfo.toStdString());
        else if(logPlace==1)
            dailylogger->info(logInfo.toStdString());
        else if(logPlace==2){
            rotatingLogger->info(logInfo.toStdString());
            dailylogger->info(logInfo.toStdString());
        }
    }break;
    case 2:{
        if(logPlace==0)
            rotatingLogger->warn(logInfo.toStdString());
        else if(logPlace==1)
            dailylogger->warn(logInfo.toStdString());
        else if(logPlace==2){
            rotatingLogger->warn(logInfo.toStdString());
            dailylogger->warn(logInfo.toStdString());
        }
    }break;
    case 3:{
        if(logPlace==0)
            rotatingLogger->error(logInfo.toStdString());
        else if(logPlace==1)
            dailylogger->error(logInfo.toStdString());
        else if(logPlace==2){
            rotatingLogger->error(logInfo.toStdString());
            dailylogger->error(logInfo.toStdString());
        }
    }break;
    default:
        break;
    }

    rotatingLogger->flush();
    dailylogger->flush();
}

void SpdLoger::slt_handleLog(QString logInfo, int logLevel, int logPlace)
{
    handleLog(logInfo,logLevel,logPlace);
}

void SpdLoger::iniSpdLoger()
{
    ///循环日志_mt
    //最多10个文件循环，每个文件最多5M，近50w条记录
    auto rotatingLogger = spdlog::rotating_logger_mt(mRotatingLogger, mRotatingFloder, mMaxSize, mMaxFiles);
    rotatingLogger->set_level(spdlog::level::debug);
    //spdlog::register_logger(rotatingLogger);

    ///每日日志_mt
    //每天00:00创建日志文件
    auto dailylogger = spdlog::daily_logger_mt(mDailyLogger, mDailyFloder, mHour, mMinute);
    dailylogger->set_level(spdlog::level::debug);
    //spdlog::register_logger(dailylogger);

}

void SpdLoger::cleanOldData()
{
    QString floderPath = qApp->applicationDirPath()+"/DailyLogs";
    //qDebug()<<floderPath;
    QDir dir(floderPath);
    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs);
//    qDebug()<<fileInfoList;
//    qDebug()<<"********************************";
//    qDebug()<<fileInfoList.at(1);
    //数量大于30清除多余文件
    if(fileInfoList.count()>30){
        int nMoreFile = fileInfoList.count()-30;
        //删除第0-nMoreFile个文件
        for(int i=0;i<nMoreFile;i++){
            QString strPath = fileInfoList.at(i).absoluteFilePath();
            QFileInfo FileInfo(strPath);
            if (FileInfo.isFile())//如果是文件
                QFile::remove(strPath);
        }
    }

}
