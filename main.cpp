#include <iostream>
#include <string>

void print_header() {
    // ASCII Art Generator: https://patorjk.com/software/taag/
    std::cout << R"( _____  _____  ___________ _____ _______   __)" << std::endl
              << R"(/  __ \/  ___||  _  | ___ \  ___/  ___\ \ / /)" << std::endl
              << R"(| /  \/\ `--. | | | | |_/ / |__ \ `--. \ V /)" << std::endl
              << R"(| |     `--. \| | | |  __/|  __| `--. \ \ /)" << std::endl
              << R"(| \__/\/\__/ /\ \_/ / |   | |___/\__/ / | |)" << std::endl
              << R"( \____/\____/  \___/\_|   \____/\____/  \_/)" << std::endl;
}

int handle_commands(std::string input) {
    if (input == "initialize") {
        std::cout << input << " command recognized. Doing something.\n";
    } else if (input == "screen") {
        std::cout << input << " command recognized. Doing something.\n";
    } else if (input == "scheduler-start") {
        std::cout << input << " command recognized. Doing something.\n";
    } else if (input == "scheduler-stop") {
        std::cout << input << " command recognized. Doing something.\n";
    } else if (input == "report-util") {
        std::cout << input << " command recognized. Doing something.\n";
    } else if (input == "clear") {
        std::cout << "\033[2J\033[H";
        print_header();
    } else if (input == "exit") {
        std::cout << "Exiting...\n";
        return 1;
    } else {
        std::cout << "Unknown command.\n";
    }

    return 0;
}

int main() {
    std::string input;
    bool is_exit = false;

    print_header();

    while(!is_exit) {
        std::cout << "Enter a command: ";
        std::getline(std::cin, input);

        is_exit = handle_commands(input);
    }

    return 0;
}