//
// Created by Fanghao Meng on 2023-07-12.
//

#include "Station.h"
#include <algorithm>

namespace sdds{
    size_t Station::m_widthField{0};
    size_t Station::id_generator{0};

    Station::Station(const std::string &src) {
        Utilities util;
        bool more = true;
        size_t pos{0};
        m_stationId = ++id_generator;

        try {
            m_name = util.extractToken(src, pos, more);
            m_serialNumber = stoi(util.extractToken(src, pos, more));
            m_itemNum = stoi(util.extractToken(src, pos, more));
            Station::m_widthField = std::max(util.getFieldWidth(), Station::m_widthField);
            m_description = util.extractToken(src, pos, more);
        }
        catch (const std::string err) {
           std::cout << err;
        }
        catch (const char* err) {
            std::cout << err;
        }
    }
    const std::string& Station::getItemName() const{
        return m_name;
    }
    size_t Station::getNextSerialNumber(){
        ++m_serialNumber;
        return m_serialNumber - 1;
    }
    size_t Station::getQuantity() const{
        return m_itemNum;
    }
    void Station::updateQuantity(){
        m_itemNum == 0 ? m_itemNum = 0 : --m_itemNum;
    }
    void Station::display(std::ostream& os, bool full) const{
        os << std::setw(3) << std::setfill('0') << std::right << m_stationId << " | ";
        os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_name;
        os << "| " << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";

        if (full)
        {
            os << std::setw(m_widthField) << std::setw(4)   << std::right << std::setfill(' ') << m_itemNum << " | ";
            os << m_description;
        }
        os << std::endl;
    }



}


