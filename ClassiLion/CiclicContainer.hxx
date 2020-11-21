/*********************************************************************
 * 
 * Conteiner whith a ciclic structure, implemented because is usefull
 * for rappresenting polygon
 * 
 *********************************************************************/

# pragma once

# include <vector>

template<typename T>
struct CiclicContainer : public std::vector<T>
{
    CiclicContainer(int N = 1): std::vector<T>(N) {}

    //-------------Metods--------------

    // Overwriting of the [] operator to build the ciclic structure
    T & operator[] (int n)
    {
        auto it = this->begin();

        return *(it + n % this->size());
    }
};
