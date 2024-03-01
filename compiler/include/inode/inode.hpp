#pragma once

#include <memory>

namespace paracl
{

        class inode_t
        {
                public:
                        virtual int  execute (inode_t &scope_)          = 0;
                        virtual void dump    () const                   = 0;
                        virtual std::unique_ptr<inode_t> clone () const = 0;

                        virtual ~inode_t () {}
        };

        using inode_u_ptr = std::unique_ptr<inode_t>;

        enum class types_t
        {
                MUL,
                PLUS,
                MINUS,
                DIV,
                MODULO,
                ASSIGN,

                EQUAL,
                NOT_EQUAL,
                GREATER,
                LESS,
                LS_EQUAL,
                GR_EQUAL,

                OUTPUT,
                INPUT,

                NUMBER,
                NAME,
                VAR,

                OR,
                AND,

                UNKOWN,
        };
}
