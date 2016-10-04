#include <stdlib.h>

#include "client.h"

Client::Client()
{

}

Client::Client(Time*& arrival_time, Time*& exit_time)
{
    total_purchases_= rand() %98 + 2;
    set_total_purchases_value();
    set_pay_type();
    set_queue_type();
    arrival_time_ = arrival_time;
    exit_time_ = exit_time;
}

void Client::set_queue_type()
{
    int queue_type = rand() %1;

    if (queue_type == 1) {
        queue_type_ = QueueType::less_Products;
    } else {
        queue_type_ = QueueType::less_size;
    }
}

void Client::set_pay_type()
{
    int pay_type = rand() %100;

    if (pay_type < 80) {
        pay_type_ = PayType::card;
    } else {
        pay_type_ = PayType::cash;
    }
}

void Client::set_total_purchases_value()
{
    for (auto i = 0; i < total_purchases_; i++) {
        total_purchases_value_ += rand()%89 + 1;
    }
}

Client::~Client()
{

}

Time* Client::get_arrival_time()
{
    return arrival_time_;
}

Time* Client::get_exit_time()
{
    return exit_time_;
}

PayType Client::get_pay_type()
{
    return pay_type_;
}

QueueType Client::get_queue_type()
{
    return queue_type_;
}

unsigned int Client::get_total_purchases()
{
    return total_purchases_;
}

double Client::get_total_value()
{
    return total_purchases_value_;
}
