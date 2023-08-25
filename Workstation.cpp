//
// Created by Fanghao Meng on 2023-07-28.
//

#include "Workstation.h"
using namespace std;
namespace sdds {
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }


    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty())

            m_orders.front().fillItem(*this, os);
    }
//    `bool attemptToMoveOrder()` – attempts to move the order order at the front of the queue to the next station in the assembly line:
//    - if the order requires no more service at this station or cannot be filled (not enough inventory), move it to the next station; otherwise do nothing
//    - if there is no next station in the assembly line, then the order is moved into `g_completed` or `g_incomplete` queue
//    - if an order has been moved, return `true`; `false` otherwise.
    bool Workstation::attemptToMoveOrder() {
        bool move_result = false;
        if (!m_orders.empty()) {
            if (m_orders.front().isItemFilled(getItemName())) {
                if (m_pNextStation)
                    *m_pNextStation += std::move(m_orders.front());
                else if (!m_orders.front().isOrderFilled())
                    g_incomplete.push_back(std::move(m_orders.front()));
                else
                    g_completed.push_back(std::move(m_orders.front()));

                move_result = true;
                m_orders.pop_front();
            } else if (this->getQuantity() <= 0) {
                if (m_pNextStation)
                    *m_pNextStation += std::move(m_orders.front());
                else
                    g_incomplete.push_back(std::move(m_orders.front()));

                move_result = true;
                m_orders.pop_front();
            }

        }
        return move_result;
    }


    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream &os) const {
        if (m_pNextStation)
            os << getItemName() << " --> " << m_pNextStation->getItemName() << endl;
        else
            os << getItemName() << " --> " << "End of Line" << endl;
    }

}


