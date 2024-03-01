#pragma once

#include "inode.hpp"
#include "symtable.hpp"
#include "scope.hpp"

namespace backend
{

class if_t : public bin_operator_t
{
        protected:
                std::unique_ptr<scope_t> scope = nullptr;
        public:
                if_t (inode_u_ptr &&condition_, inode_u_ptr &&else_scope_, inode_u_ptr scope_ = nullptr):
                        bin_operator_t(std::move(condition_), std::move(else_scope_)), scope(static_cast<scope_t*>(scope_.release()))
                { scope->insert_symbs(lhs.get(), types_t::UNKOWN); if (!lhs) throw std::runtime_error("If_t must have condition."); }

                if_t (inode_u_ptr &&condition_, inode_u_ptr scope_ = nullptr):
                        bin_operator_t(std::move(condition_), nullptr), scope(static_cast<scope_t*>(scope_.release()))
                { scope->insert_symbs(lhs.get(), types_t::UNKOWN); if (!lhs) throw std::runtime_error("If_t must have condition."); }

                if_t (inode_t *condition_, inode_t *else_scope_, scope_t *scope_ = nullptr):
                        bin_operator_t(condition_, else_scope_), scope(scope_)
                { scope->insert_symbs(lhs.get(), types_t::UNKOWN); if (!lhs) throw std::runtime_error("If_t must have condition."); }

                if_t (inode_t *condition_, scope_t *scope_ = nullptr):
                        bin_operator_t(condition_, nullptr), scope(scope_)
                { scope->insert_symbs(lhs.get(), types_t::UNKOWN); if (!lhs) throw std::runtime_error("If_t must have condition."); }

                if_t (const if_t &rhs_) : bin_operator_t(rhs_), scope(rhs_.scope->clone_raw()) {}
                if_t (if_t &&rhs_) = default;
                if_t& operator=(if_t &&rhs_) = default;

                virtual ~if_t () {}

                inline int execute (inode_t& scope_) override;
                inline void dump () const override;
                inode_u_ptr clone () const override
                { return inode_u_ptr(new if_t {lhs->clone(), rhs ? rhs->clone() : nullptr, scope->clone()}); }

                void insert (inode_t *node_) { scope->insert(node_); }

                bool is_visible (const std::string &name) { return scope->find(name) ? true : false; }
                scope_t* get_scope () { return scope.get(); }
};

class while_t final : public if_t
{
        public:
                while_t (inode_u_ptr &&condition_, inode_u_ptr scope_ = nullptr):
                         if_t(std::move(condition_), nullptr, std::move(scope_)) {}
                while_t (inode_t *condition_, scope_t *scope_ = nullptr):
                        if_t(condition_, scope_) {}
                while_t (const while_t &rhs_) = default;
                while_t (while_t &&rhs_) = default;
                while_t& operator=(while_t &&rhs_) = default;
                while_t& operator=(const while_t &rhs_) { return *this = while_t {rhs_}; }
                ~while_t () = default;

                inline int execute (inode_t& scope_) override;
                inode_u_ptr clone () const override
                { return inode_u_ptr(new while_t {lhs->clone(), scope->clone()}); }
                
                inline void dump () const override;
};

//===================================================~~~DECLARATIONS~~~====================================================================

//---------------------------------------------------~~~~~~Public~~~~~~--------------------------------------------------------------------

inline int if_t::execute (inode_t& scope_)
{
        if (lhs->execute(scope_))
                return scope->execute(scope_);
        else if (rhs)
                return rhs->execute(scope_);

        return 0;
}

inline void if_t::dump () const
{
        std::cout << "if (";
        lhs->dump();
        std::cout << ")\n";
        scope->dump_uppers();
        std::cout << "\n{\n";
        scope->dump();
        std::cout << "}\n";
        if (rhs)
                rhs->dump();
        std::cout << "\n";
}

inline int while_t::execute (inode_t& scope_)
{
        while (lhs->execute(scope_))
                scope->execute(scope_);

        return 0;
}

inline void while_t::dump () const
{
        std::cout << "while (";
        lhs->dump();
        std::cout << ")\n";
        scope->dump_uppers();
        std::cout << "\n{\n";
        scope->dump();
        std::cout << "}\n";
        if (rhs)
                rhs->dump();
        std::cout << "\n";
}

inline inode_t* create_if (inode_t *condition_, scope_t *scope_, inode_t *else_scope = nullptr)
{
        return new if_t {condition_, else_scope, scope_};
}

inline inode_t* create_while (inode_t *condition_, scope_t *scope_)
{
        return new while_t {condition_, scope_};
}

}
