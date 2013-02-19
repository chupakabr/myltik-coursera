/**
 * Created with IntelliJ IDEA.
 * User: myltik
 * Date: 2/16/13
 * Time: 11:04 PM
 *
 * week2_solution1 interface.
 */

#ifndef __week2_solution1_hpp
#define __week2_solution1_hpp

#include <string>
#include "week2_solution.hpp"

class week2_solution1 : public week2_solution {

public:
    week2_solution1(const char * filename) : week2_solution(filename) {}

    virtual pivotp pivot_point(val_collection_ptr_t & lst, const int i, const int j) {
        val_collection_t::const_iterator it = lst->begin();
        std::advance(it, i);

        return (pivotp) {*it, i};
    }
};

#endif