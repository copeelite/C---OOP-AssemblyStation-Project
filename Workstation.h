//
// Created by Fanghao Meng on 2023-07-28.
//
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
namespace sdds{
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders;
        Workstation *m_pNextStation { nullptr };
    public:
        Workstation(const std::string& str) : Station(str) {}

        Workstation(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation& operator=(Workstation&&) = delete;


        Workstation& operator+=(CustomerOrder&& newOrder);
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
    };
}
#endif //SDDS_WORKSTATION_H
