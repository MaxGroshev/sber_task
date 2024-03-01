#include "elems.hpp"
#include "scope.hpp"

namespace backend {

int name_t::execute (inode_t& scope_)
{
        auto var = static_cast<scope_t*>(&scope_)->find(*this);
        if (var) {
                // std::cout << "exec name " << var->execute(scope_) << " " << static_cast<var_t<int>*>(var)->get_name() << "\n";
                return var->execute(scope_);
        } else {
                // std::cout << "execute name\n";
                static_cast<scope_t*>(&scope_)->insert_symbs(this, types_t::VAR);
        }
        return 0;
}

}
