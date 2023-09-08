#include "CategoryController.h"

void Category::print_list()
{
    std::cout << "AVAILABLE CATEGORIES !" << '\n';
    for (auto it = this->list.begin(); it != this->list.end(); it++) {
        std::cout << "id : " << (*it).first << '\n';
        std::cout << "Category : " << (*it).second << '\n';
    }
}
