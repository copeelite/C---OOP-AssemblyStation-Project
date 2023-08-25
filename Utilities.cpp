//
// Created by Fanghao Meng on 2023-07-12.
//
#include "Utilities.h"
#include "algorithm"
namespace sdds {
    char Utilities::m_delimiter = '\0';

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        std::string token;
        size_t former_pos = next_pos;

        next_pos = str.find(m_delimiter, former_pos);

        if (former_pos == next_pos)
        {
            more = false;
            throw "   ERROR: No token.\n";
        }
        else if (next_pos == std::string::npos)
        {
            token = str.substr(former_pos);
            m_widthField = std::max(token.length(), m_widthField);
            more = false;
        }
        else
        {
            token = str.substr(former_pos, next_pos - former_pos);
            m_widthField = std::max(token.length(), m_widthField);
            more = true;
        }

        if (token.length() > 0)
        {
            if (token[0] == ' ')
                token.erase(0, token.find_first_not_of(' '));

            if (token[token.length() - 1] == ' ')
                token.erase(token.find_last_not_of(' ') + 1);
        }

        if (token.length() > m_widthField)
            setFieldWidth(token.length());

        next_pos++;

        return token;
    }

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
}
