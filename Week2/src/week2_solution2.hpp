/**
 * Created with IntelliJ IDEA.
 * User: myltik
 * Date: 2/17/13
 * Time: 12:23 AM
 *
 * week2_solution2 interface.
 */

#ifndef __week2_solution2_hpp
#define __week2_solution2_hpp

#include <string>
#include "week2_solution.hpp"

class week2_solution2 : public week2_solution {

public:
    week2_solution2(const char * filename) : week2_solution(filename) {}

    virtual pivotp pivot_point(val_collection_ptr_t & lst, const int i, const int j) {
        val_collection_t::const_iterator it = lst->begin();
        std::advance(it, j);

        return (pivotp) {*it, j};
    }
};

#endif