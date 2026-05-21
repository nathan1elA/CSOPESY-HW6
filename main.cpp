#include <iostream>
#include <string>

void print_header() {
    const std::string resetText = "\033[0m";
    const std::string greenText = "\033[32m";
    const std::string yellowText = "\033[33m";

    // ASCII Art Generator: https://patorjk.com/software/taag/
    std::cout << R"( _____  _____  ___________ _____ _______   __)" << std::endl
              << R"(/  __ \/  ___||  _  | ___ \  ___/  ___\ \ / /)" << std::endl
              << R"(| /  \/\ `--. | | | | |_/ / |__ \ `--. \ V /)" << std::endl
              << R"(| |     `--. \| | | |  __/|  __| `--. \ \ /)" << std::endl
              << R"(| \__/\/\__/ /\ \_/ / |   | |___/\__/ / | |)" << std::endl
              << R"( \____/\____/  \___/\_|   \____/\____/  \_/)" << std::endl;

    std::cout << greenText << "Hello, Welcome to CSOPESY commandline!" << resetText << std::endl;
    std::cout << yellowText << "Type 'exit' to quit, 'clear' to clear the screen" << resetText << std::endl << '\n';
    std::cout << yellowText << "** IMPORTANT: Type 'initialize' to load config and start system **" << resetText << std::endl;
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