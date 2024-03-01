#pragma once

#include <string>

#include "inode/inode.hpp"

namespace backend {

using namespace paracl;

class node_error_t : public inode_t
{
        public:
        std::string what = {};

        node_error_t (std::string what_ = "Error") : what(what_) {}

        int execute (inode_t &scope_) override
        { throw std::runtime_error(what); }

        std::unique_ptr<inode_t> clone () const override
        { return std::unique_ptr<inode_t>(new node_error_t {what}); }

        void dump () const override
        { std::cerr << what << std::endl; }
};

inline inode_t* create_error (std::string what = "Unknown error") { return new node_error_t {what}; }

class empty_node_t : public inode_t
{
        public:
        empty_node_t () {}

        int execute (inode_t &scope_) override
        { return 0; }

        std::unique_ptr<inode_t> clone () const override
        { return std::unique_ptr<inode_t>(new empty_node_t {}); }

        void dump () const override
        { std::cerr << ";" << std::endl; }
                
};

inline inode_t* create_empty () { return new empty_node_t {}; }

}
