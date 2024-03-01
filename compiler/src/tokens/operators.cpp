#include "operators.hpp"
#include "scope.hpp"

using namespace backend;

int assign_t::execute (inode_t& scope_)
{
        auto status = check_node_type(lhs.get());
        if (!status)
                throw std::runtime_error("Cannot assign to that type");   //TODO

        if (typeid(*lhs) == typeid(name_t) || typeid(*lhs) == typeid(var_t<int>)) {
                auto var = static_cast<scope_t*>(&scope_)->find(*static_cast<name_t*>(lhs.get()));
                if (!var)
                        var = static_cast<scope_t*>(&scope_)->insert_symbs(lhs.get(), types_t::VAR);

                *static_cast<var_t<int>*>(var) = rhs->execute(scope_);
                return (*static_cast<var_t<int>*>(var)).get_data(); //TODO!!!!!!!!
        }

        throw std::runtime_error("Unkown type!");
}
