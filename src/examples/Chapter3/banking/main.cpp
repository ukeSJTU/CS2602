#include <cstdlib>  // 用于随机数生成
#include <ctime>    // 用于随机数种子
#include <iostream>
#include <string>

#include "SeqQueue.h"

using namespace datastructures;
using namespace std;

// 顾客类，存储顾客的到达时间和业务类型
struct Customer {
    int arrivalTime;  // 到达时间（以分钟为单位，从开门时间9:00开始）
    string service;   // 业务类型
    int serviceTime;  // 业务耗时

    Customer() : arrivalTime(0), service("未知"), serviceTime(0) {}

    Customer(int time, const string& svc, int svcTime)
        : arrivalTime(time), service(svc), serviceTime(svcTime)
    {
    }
};

// 显示队列中的顾客状态
void displayQueue(SeqQueue<Customer>& queue, int queueSize)
{
    // 使用辅助队列来遍历 `SeqQueue`
    SeqQueue<Customer> tempQueue;
    cout << "排队人数：" << queueSize << "，排队信息：";
    while (!queue.isEmpty()) {
        Customer front = queue.front();
        queue.deQueue();
        cout << "{" << front.service << ", " << front.serviceTime << "分钟} ";
        tempQueue.enQueue(front);
    }
    cout << endl;

    // 恢复原队列状态
    while (!tempQueue.isEmpty()) {
        queue.enQueue(tempQueue.front());
        tempQueue.deQueue();
    }
}

// 格式化时间为 "hh:mm"
string formatTime(int time)
{
    int hour = time / 60;
    int minute = time % 60;
    return to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute);
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));  // 设置随机数种子

    // 使用 SeqQueue 实现的顾客队列
    SeqQueue<Customer> queue;

    // 时间变量
    const int openingTime = 9 * 60;                       // 开门时间（9:00）
    const int closingTime = 16 * 60 + 30;                 // 关门时间（16:30）
    int currentTime = openingTime;                        // 当前时间
    int nextArrivalTime = currentTime + 10 + rand() % 5;  // 第一个顾客到达时间
    int counterAvailableTime = openingTime;               // 柜台空闲时间

    int queueSize = 0;         // 用于统计排队人数
    Customer currentCustomer;  // 当前正在服务的顾客
    bool isCounterBusy = false;

    cout << "银行营业模拟开始（9:00 开门，16:30 关门）" << endl;

    while (currentTime < closingTime || queueSize > 0 || isCounterBusy) {
        // 如果到达时间到了并且在营业时间内，生成新顾客
        if (currentTime >= nextArrivalTime && currentTime < closingTime) {
            // 随机生成业务类型
            int serviceType = rand() % 3;  // 0: 取款, 1: 存款, 2: 办理网银
            string serviceName;
            int serviceTime;
            if (serviceType == 0) {
                serviceName = "取款";
                serviceTime = 2;
            } else if (serviceType == 1) {
                serviceName = "存款";
                serviceTime = 4;
            } else {
                serviceName = "办理网银";
                serviceTime = 10;
            }

            Customer customer(nextArrivalTime, serviceName, serviceTime);
            queue.enQueue(customer);
            queueSize++;
            cout << "[" << formatTime(nextArrivalTime) << "] 顾客到达，业务：" << serviceName
                 << "（预计耗时 " << serviceTime << " 分钟）" << endl;

            // 生成下一个顾客到达时间
            nextArrivalTime += 5 + rand() % 5;
        }

        // 如果柜台空闲且队列中有顾客，处理下一个顾客
        if (!isCounterBusy && queueSize > 0) {
            currentCustomer = queue.front();
            queue.deQueue();
            queueSize--;
            isCounterBusy = true;
            counterAvailableTime = currentTime + currentCustomer.serviceTime;

            cout << "[" << formatTime(currentTime) << "] 柜台开始处理顾客业务："
                 << currentCustomer.service << "（预计完成时间 " << formatTime(counterAvailableTime)
                 << "）" << endl;
        }

        // 如果柜台正在处理顾客且当前时间到达柜台空闲时间，完成业务
        if (isCounterBusy && currentTime == counterAvailableTime) {
            cout << "[" << formatTime(currentTime) << "] 顾客业务完成：" << currentCustomer.service
                 << endl;
            isCounterBusy = false;
        }

        // 显示当前队列状态
        if (queueSize > 0) {
            cout << "[" << formatTime(currentTime) << "] ";
            displayQueue(queue, queueSize);
        }

        // 时间推进
        currentTime++;
    }

    cout << "[" << formatTime(closingTime) << "] 银行营业结束！所有顾客已处理完毕。" << endl;
    return 0;
}