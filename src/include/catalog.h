#include <vector>
#include "table.h"

namespace emerald {
    class Catalog {
        private:
          std::vector<Table> TableList;
        public:
          Catalog();
          std::vector<Table> getTables();
    }
}

Catalog::Catalog(){

}

std::vector<Table> Catalog::getTables(){
    return TableList;
}