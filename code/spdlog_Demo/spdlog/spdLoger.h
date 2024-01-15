#ifndef SPDLOGER_H
#define SPDLOGER_H

///     spdlog封装说明
///     使用的spdLog的多线程模式，线程安全
///     包括同时支持两种日志形式（循环日志/每日日志）
//1：循环日志文件存储
//单个文件最多可以存储 5mb的大小，一个可存储10个文件
//默认文件地址为 执行文件目录下：RotatingLogs/rotating.txt

//2：每日日志文件存储
//每日0点0时创建新文件
//启动时检查超过30份文件时删除最前面文件的数据
//默认文件地址为 执行文件目录下：DailyLogs/daily.txt

//测试界面如图 包括debug、info、warn、err几种类型进行了分类
//支持信号槽调用




#include <QObject>

class SpdLoger : public QObject
{
    Q_OBJECT
public:
    explicit SpdLoger(QObject *parent = nullptr);
    ~SpdLoger();

    ///打印日志
    ///logInfo:  记录内容
    ///logLevel: 记录等级 0-debug,1-info-,2-warn,3-error
    ///logPlace: 日志输出位置 0-循环日志,1-每日日志,2-循环/每日日志
    void handleLog(QString logInfo,int logLevel=1,int logPlace=0);

public slots:
    void slt_handleLog(QString logInfo,int logLevel=1,int logPlace=0);
private:
    //初始化日志
    void iniSpdLoger();
    //清理历史数据(dailyLog)
    static void cleanOldData();
signals:

private:
    /// 循环日志参数
    int mMaxSize  = 5000/*1048576 * 5*/;                                //单个文件最大数据量
    int mMaxFiles = 10;                                         //循环文件个数
    std::string mRotatingFloder = "RotatingLogs/rotating.txt";  //循环文件地址
    std::string mRotatingLogger = "rotatingLogger";             //循环日志名

    /// 每日日志参数
    int mHour   = 0;                                            //每日创建时间-hour
    int mMinute = 0;                                            //每日创建时间-min
    std::string mDailyFloder    = "DailyLogs/daily.txt";        //循环文件地址
    std::string mDailyLogger    = "dailyLogger";                //每日日志名

};

#endif // SPDLOGER_H
