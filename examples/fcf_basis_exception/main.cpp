#define FCF_BASIS_IMPLEMENTATION
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fcfBasis/basis.hpp>

/**
 * @brief Example application: Working with the fcf::Exception system.
 *
 * In this example, we will cover:
 * 1. Using built-in library exceptions.
 * 2. Creating a custom exception type with parameters.
 * 3. Using message formatting templates.
 * 4. Handling exception hierarchies.
 */

// --- 1. Creating custom exceptions ---

/**
 * @brief Custom exception to demonstrate parameter passing.
 *
 * The FCF_EXCEPTION_DECLARE macro takes:
 * - am_type: Name of the new class.
 * - am_name: String name of the error (will be displayed in fcf::Exception::name()).
 * - am_message: Message template. Use ${{1}}, ${{2}} to insert arguments.
 * - am_argCount: Number of arguments the exception will store.
 *
 * Exception arguments can be passed as arbitrary types, as they are stored in an fcf::Variant object.
 */
FCF_EXCEPTION_DECLARE(DatabaseConnectionException, "DATABASE_CONNECTION_ERROR",
                      "Failed to connect to database '${{1}}$' on port ${{2}}$. Error code: ${{3}}$", 3);

/**
 * @brief Another exception demonstrating "sub-exceptions" (error chaining).
 * This is useful for creating error chains.
 */
FCF_EXCEPTION_DECLARE(DataProcessingException, "DATA_PROCESSING_ERROR",
                      "Critical error during processing: ${{1}}$", 1);


// --- 2. Helper functions for demonstration ---

void connectToDatabase(const std::string& dbName, int port, int errorCode) {
    std::cout << "[System] Attempting to connect to " << dbName << "..." << std::endl;
    // Simulate an error
    throw DatabaseConnectionException(__FILE__, __LINE__, dbName, port, errorCode);
}

void processData(int value) {
    if (value < 0) {
        // Create an exception and "wrap" it with another exception (chaining)
        try {
            throw DataProcessingException(__FILE__, __LINE__, "Negative value encountered");
        } catch (const fcf::Exception& e) {
            throw DataProcessingException(e, __FILE__, __LINE__, "Wrapped error");
        }
    }
    std::cout << "[System] Processing value: " << value << std::endl;
}


// --- 3. Main logic ---

int main() {
    std::cout << "=== [1] Demonstration of custom exception with parameters ===" << std::endl;
    std::cout << std::endl;
    try {
        connectToDatabase("Production_DB", 5432, 404);
    } catch (const fcf::Exception& e) {
        std::cout << "Caught Exception: " << e.name() << std::endl;
        // The full() method prints the complete error tree with formatted messages
        std::cout << "Full Info:\n" << e.full() << std::endl;
    }

    std::cout << "\n=== [2] Demonstration of exception chaining (Sub-exceptions) ===" << std::endl;
    std::cout << std::endl;
    try {
        processData(-10);
    } catch (const fcf::Exception& e) {
        std::cout << "Caught Exception: " << e.name() << std::endl;
        std::cout << std::endl;
        std::cout << "Manual processing of information output:" << std::endl;
        std::cout << "  Message: " << e.message() << std::endl;
        std::cout << "  Position: " << e.position() << std::endl;
        // Handling nested exceptions
        if (e.subSize() > 0) {
            std::cout << "  Detected " << e.subSize() << " sub-exception(s):" << std::endl;
            for (size_t i = 0; i < e.subSize(); ++i) {
                std::cout << "    [" << i + 1 << "] " << e.sub(i).message() << std::endl;
            }
        }

        // Outputting basic exception information
        std::cout << std::endl;
        std::cout << "Outputting information using the info() method:" << std::endl;
        std::string infoWithIdent = e.info();
        infoWithIdent = std::regex_replace(e.info(), std::regex("^|\n"), "$&  ");
        std::cout << infoWithIdent << std::endl;

        // Outputting all exception information
        std::cout << std::endl;
        std::cout << "Outputting information using the full() method:" << std::endl;
        std::string fullWithIdent = e.full();
        fullWithIdent = std::regex_replace(e.full(), std::regex("^|\n"), "$&  ");
        std::cout << fullWithIdent << std::endl;

    }

    std::cout << "\n=== [3] Demonstration of built-in fcf exceptions ===" << std::endl;
    std::cout << std::endl;
    try {
        // Simulate a situation where a function is not found (built-in exception)
        // In reality, this happens inside call/rcall mechanisms
        throw fcf::CallNotFoundException(__FILE__, __LINE__, "my_missing_func", "void(int)");
    } catch (const fcf::Exception& e) {
        std::cout << "Caught Built-in: " << e.name() << std::endl;
        std::cout << "Formatted Message: " << e.message() << std::endl;
    }

    return 0;
}