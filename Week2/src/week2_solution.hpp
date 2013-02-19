/**
 * Created with IntelliJ IDEA.
 * User: myltik
 * Date: 2/17/13
 * Time: 12:14 AM
 *
 * week2_solution interface.
 */

#ifndef __week2_solution_hpp
#define __week2_solution_hpp

#include <string>
#include <list>
#include <memory>
#include <fstream>


//
// Types

typedef int val_t;
typedef std::list<val_t> val_collection_t;
typedef std::unique_ptr<val_collection_t> val_collection_ptr_t;

typedef struct pivotp_t {
    val_t value;
    int index;
} pivotp;


//
// Helpers

void print_list(val_collection_ptr_t & lst, const char * ns) {
    std::cout << ns << ": ";
    std::for_each(lst->begin(), lst->end(), [](val_t val) {
        std::cout << val;
    });
    std::cout << std::endl;
}


//
// Solution

class week2_solution {

private:
    const std::string filename_;
    int comparison_count_;

    void quick_sort(val_collection_ptr_t & lst, const int i, const int j) {
        if (j - i < 1) return;

        pivotp pp = pivot_point(lst, i, j);
//        std::cout << "quick_sort(" << lst.get() << ", " << i << ", " << j << "), pp=" << pp.value << " at " << pp.index << std::endl;

        // Swap pivot point with the first element
        swap_elements(lst, i, pp.index);

        // Sort current set
        int downidx = i+1;
        int upidx = downidx;
        val_collection_t::iterator it = lst->begin();
        std::advance(it, downidx);
        for (; upidx <= j; ++upidx, ++it, ++comparison_count_) {
            if (pp.value > *it) {
                swap_elements(lst, downidx, upidx);
                ++downidx;
            }
        }

        // Swap pivot point with the latest value from left-subset
        int pivotidx = downidx-1;
        swap_elements(lst, i, pivotidx);

        // Call quick_sort for both subsets
//        std::cout << "before call: i=" << i << ", pivotidx=" << pivotidx << ", downidx=" << downidx << ", upidx=" << upidx << std::endl;
        quick_sort(lst, i, pivotidx-1);
        quick_sort(lst, pivotidx+1, upidx-1);
    }

    void swap_elements(val_collection_ptr_t & lst, int idx1, int idx2) {
        if (idx1 == idx2) return;

        val_collection_t::iterator firstit = lst->begin();
        std::advance(firstit, idx1);

        val_collection_t::iterator secondit = lst->begin();
        std::advance(secondit, idx2);

        val_t tmp = *firstit;
        (*firstit) = *secondit;
        (*secondit) = tmp;
    }

protected:
    week2_solution(const char * filename)
        : filename_(filename)
          ,comparison_count_(0)
    {}
    virtual ~week2_solution() {}

    virtual pivotp pivot_point(val_collection_ptr_t & lst, const int i, const int j) = 0;

public:
    std::unique_ptr<std::list<val_t>> run() {
        // Load, parse file and run quick_sort on constructed list
        val_collection_ptr_t lst(new val_collection_t());

        std::ifstream infile(filename_);
        if (!infile.good()) {
            std::cerr << "File [" << filename_ << "] does not exists" << std::endl;
            exit(127);
        }

        val_t val;
        while (infile >> val) {
            lst->push_back(val);
        }

//        lst->push_back(1);
//        lst->push_back(5);
//        lst->push_back(3);
//        lst->push_back(8);
//        lst->push_back(4);
//        lst->push_back(7);
//        print_list(lst, "initial");

        // Sort
        quick_sort(lst, 0, lst->size()-1);
        return lst;
    }

    int comparison_count() const {
        return comparison_count_;
    }
};

#endif