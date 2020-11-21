/*********************************************************************
 * 
 * Container with a ciclic structure, implemented because is usefull
 * for rappresenting polygons
 * 
 *********************************************************************/

# pragma once

# include <vector>

template<typename T>
struct ciclicVector : public std::vector<T>
{
    ciclicVector(int N): std::vector<T>(N) {}
    ciclicVector() : std::vector<T>() {}

    //-------------Methods--------------

    // Overwriting of the [] operator to build the ciclic structure
    T & operator[] (int n)
    {
        auto it = this->begin();

        return *(it + n % this->size());
    }
};
