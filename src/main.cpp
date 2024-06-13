#include "io.h"
#include "text.h"
#include "console.h"

#include <vector>

int main() {
    std::string line = console::file_input();
    console::exit_if_q( line );
    const int limit = console::get_char_limit();
    const auto filename = console::get_name( line );

    const std::vector<std::string> perms = GeneratePermutations( io_utils::GetWords( line ), limit );
    io_utils::WritePerms(std::to_string(console::nanos()) + "_" + filename, perms );
}