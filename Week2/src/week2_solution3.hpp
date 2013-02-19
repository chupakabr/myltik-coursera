/**
 * Created with IntelliJ IDEA.
 * User: myltik
 * Date: 2/17/13
 * Time: 12:23 AM
 *
 * week2_solution3 interface.
 */

#ifndef __week2_solution3_hpp
#define __week2_solution3_hpp

#include <string>
#include <algorithm>
#include <math.h>
#include "week2_solution.hpp"

class week2_solution3 : public week2_solution {

public:
    week2_solution3(const char * filename) : week2_solution(filename) {}

    virtual pivotp pivot_point(val_collection_ptr_t & lst, const int i, const int j) {
        val_collection_t::const_iterator it = lst->begin();

        // 10-0/2 = 5 = 5+0 = 5 (0 1 2 3 4   5   6 7 8 9 10)
        // 10-1/2 = 4.5 = 4+1 = 5 (1 2 3 4    5    6 7 8 9 10)
        // 10-3/2 = 3.5 = 3+3 = 6 (3 4 5    6    7 8 9 10)
        // 10-4/2 = 3 = 3+4 = 7 (4 5 6   7   8 9 10)
        int mididx = i + floor((j-i)/2);
        std::advance(it, mididx);
        pivotp mid = {*it, mididx};

        it = lst->begin();
        std::advance(it, i);
        pivotp min = {*it, i};

        it = lst->begin();
        std::advance(it, j);
        pivotp max = {*it, j};

        return middle(min, max, mid);
    }

private:

    // 1 2 3:
    //  1 <= 2, 3 < 2 ? ... : 2
    // 2 1 3:
    //  2 > 1, 3 < 2 ? ... : 2
    // 3 1 2:
    //  3 > 1, 2 < 3 ? (2 > 1 ? 2 : 1) : ...
    // 1 3 2:
    //  1 <= 3, 2 < 3 ? (2 > 1 ? 2 : 1) : ...
    pivotp middle(const pivotp v1, const pivotp v2, const pivotp v3) {
        if (v1.value > v2.value) {
            return v3.value < v1.value ? (v3.value > v2.value ? v3 : v2) : v1;
        }
        else {//v1 <= v2
            return v3.value < v2.value ? (v3.value > v1.value ? v3 : v1) : v2;
        }
    }
};

#endif