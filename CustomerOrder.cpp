//
// Created by Fanghao Meng on 2023-07-23.
//
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"


namespace sdds
{

    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder(const std::string& src)
    {
        Utilities util;
        bool more    = true;
        size_t pos   = 0u;
        size_t idx   = 0u;

        try {
            m_name = util.extractToken(src, pos, more);
            m_product = util.extractToken(src, pos, more);
            m_cntItem = std::count(src.begin(), src.end(), util.getDelimiter()) - 1;

            if (m_cntItem)
                m_lstItem = new Item*[m_cntItem];

            while (more && m_cntItem) {
                m_lstItem[idx] = new Item(util.extractToken(src, pos, more));
                ++idx;
            }

            CustomerOrder::m_widthField = std::max(util.getFieldWidth(), CustomerOrder::m_widthField);
        }
        catch (std::string err) {
            std::cout << err;
        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& src) {
        throw false;
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
        *this = std::move(src);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
        if (this != &src) {
            if (m_lstItem) {
                for (auto i = 0u; i < m_cntItem; ++i)
                    delete m_lstItem[i];

                delete[] m_lstItem;
            }

            m_name    = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;

            src.m_name    = "";
            src.m_product = "";
            src.m_cntItem = 0;
            src.m_lstItem = nullptr;
        }

        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        if (m_lstItem) {
            for (auto i = 0u; i < m_cntItem; ++i)
                delete m_lstItem[i];

            delete[] m_lstItem;
            m_lstItem = nullptr;
        }
    }

    bool CustomerOrder::isOrderFilled() const {
        bool result = true;

        for (auto i = 0u; i < m_cntItem; ++i) {
            if (!m_lstItem[i]->m_isFilled)
                result = false;
        }

        return result;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        bool result = true;
        for (auto i = 0u; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
                result = false;
        }

        return result;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        bool isItemFound = false;
        //&& !isItemFilled
        for (auto i = 0; i < m_cntItem && !isItemFound; ++i)
        {

                if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled) {
                    if (station.getQuantity() > 0) {
                        station.updateQuantity();
                        m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                        m_lstItem[i]->m_isFilled = true;
                        isItemFound = true;
                        os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;

                        //os <<isItemFilled(station.getItemName()) << std::endl;
                        //isItemFilled = true;

                    }
                    else os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
        }


    }


    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;

        for (auto i = 0u; i < m_cntItem; ++i) {
            os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
            os << std::left << std::setw(CustomerOrder::m_widthField - 1) << std::setfill(' ') << m_lstItem[i]->m_itemName;
            os << "- " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }
}