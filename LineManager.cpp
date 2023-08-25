//
// Created by Fanghao Meng on 2023-07-28.
//
#include "LineManager.h"
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include "Utilities.h"
using namespace std;
namespace sdds {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        Utilities temp_util;
        string    eachLine = "", cur_Wstation = "", next_Wstation = "";
        size_t    pos = 0u;
        bool      more = false;
        vector<string> v_cur_Wstation, v_next_Wstation;

        ifstream  read_file(file);

        if (!read_file)
            throw string("\n***Failed to open file ") + string(file) + string(" ***\n");

        else {
            //std::cout << "read the file now" << std::endl;
            while (std::getline(read_file, eachLine)) {
                if (!eachLine.empty()) {
                    cur_Wstation = temp_util.extractToken(eachLine, pos, more);
                    v_cur_Wstation.push_back(cur_Wstation);

                    next_Wstation = !more ? "" : temp_util.extractToken(eachLine, pos, more);
                    v_next_Wstation.push_back(next_Wstation);

                    auto cur_err_check = any_of(stations.begin(), stations.end(), [=](Workstation* first_src) {
                        if (first_src->getItemName() == cur_Wstation) {
                            if (!next_Wstation.empty()) {
                                auto next_err_check = any_of(stations.begin(), stations.end(), [=](Workstation* sec_src) {
                                    if (sec_src->getItemName() == next_Wstation) {
                                        first_src->setNextStation(sec_src);
                                        return true;
                                    }
                                    else
                                        return false;
                                });

                                if (!next_err_check) throw string("\n\n***Next Workstation is not found***\n\n");
                                else if (cur_Wstation == next_Wstation) throw string("\n\n***Next Workstation is not found***\n\n");
                            }
                            m_activeLine.push_back(first_src);
                            return true;
                        }

                        else
                            return false;
                    });

                    if (!cur_err_check)
                        throw string("\n\n***Something went wrong***\n\n");
                }
            }
            read_file.close();

            for_each(m_activeLine.begin(), m_activeLine.end(), [=](Workstation* first_src) {
                auto start = any_of(stations.begin(), stations.end(), [=](Workstation* sec_src) {
                    if (sec_src->getNextStation() == first_src)
                        return true;
                    else
                        return false;
                });

                if (!start)
                    m_firstStation = first_src;
            });

            m_cntCustomerOrder = g_pending.size();
        }
    }

    void LineManager::reorderStations() {
        Workstation* next_Wstation = m_firstStation;
        vector<Workstation*>  v_Wstation;

        while (next_Wstation) {
            v_Wstation.push_back(next_Wstation);
            next_Wstation = next_Wstation->getNextStation();
        }

        m_activeLine = v_Wstation;
    }




    bool LineManager::run(std::ostream& os) {
        static size_t count = 0u;

        os << "Line Manager Iteration: " << ++count << endl;


        if (!g_pending.empty()) {
            *m_activeLine.front() += move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto src : m_activeLine)
            src->fill(os);

        for (auto src : m_activeLine)
            src->attemptToMoveOrder();

        return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();
    }





    void LineManager::display(std::ostream& os) const {
        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* src) {
            src->display(os);
        });
    }

}

