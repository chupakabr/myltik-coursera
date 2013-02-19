#include <iostream>
#include <iomanip>
#include <list>
#include <memory>

#include "week2_solution1.hpp"
#include "week2_solution2.hpp"
#include "week2_solution3.hpp"

#include <boost/test/unit_test.hpp>

using namespace std;

int main(int argc, const char* argv[])
{
    cout << "Week2 solution" << endl;
    cout << "--------------" << endl << endl;

    // Validate command params
    if (argc != 2) {
        cout << "No input files" << endl;
        return 1;
    }
    cout << "Input file is [" << argv[1] << "]" << endl;
    cout.flush();

    // Run all the solutions
    week2_solution1 impl1(argv[1]);
    week2_solution2 impl2(argv[1]);
    week2_solution3 impl3(argv[1]);

    // Running
    std::unique_ptr<val_collection_t> lst = impl1.run();
    cout << "Result #1: " << impl1.comparison_count() << endl;
//    print_list(lst, "res1");

    lst = impl2.run();
    cout << "Result #2: " << impl2.comparison_count() << endl;
//    print_list(lst, "res2");

    lst = impl3.run();
    cout << "Result #3: " << impl3.comparison_count() << endl;
//    print_list(lst, "res3");

    return 0;
}
