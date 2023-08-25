//
// Created by Fanghao Meng on 2023-07-10.
//

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>
#include <iomanip>
#include <string>
#include "Utilities.h"
namespace sdds{
    class Station{
        int m_stationId{};
        std::string m_name{};
        std::string m_description{};
        size_t m_serialNumber{};
        size_t m_itemNum{};
        static size_t m_widthField;
        static size_t id_generator;
    public:
        Station(const std::string& src);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;


    };
}
#endif //SDDS_STATION_H
