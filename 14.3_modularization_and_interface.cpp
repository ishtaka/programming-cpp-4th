#include <string>
#include <map>

//===--------------------------------------------------------------===//
// 14.3.1 namespace as module
//===--------------------------------------------------------------===//

namespace Parser { // interface for user
    double expr(bool);
}

namespace Lexer {
    enum class Kind : char {
    };

    class Token {
    };

    class Token_stream {
    };

    Token_stream ts;
}


namespace Table {
    std::map<std::string, double> table;
}

namespace Driver {
    void calculate() {}
}

namespace Error {
    int no_of_errors;

    double error(const std::string &s) {}
}

namespace Parser_impl { // interface for implementer
    using namespace Parser;

    double prim(bool);

    double term(bool);

    using namespace Lexer;
    using Error::error;
    using Table::table;
}

//===--------------------------------------------------------------===//
// 14.3.2 implementation
//===--------------------------------------------------------------===//

double Parser_impl::prim(bool get) {}

double Parser_impl::term(bool get) {}

double Parser::expr(bool get) {}

//===--------------------------------------------------------------===//

int main() {
    return 0;
}
