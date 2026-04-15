#define FCF_BASIS_IMPLEMENTATION
#include <iostream>
#include <string>
#include <vector>
#include <fcfBasis/basis.hpp>

/**
 * @brief Custom user type example.
 */
struct UserProfile {
    int id;
    std::string username;
};

// Register the type in the fcf system so it can participate in conversions.
FCF_TYPEID_REGISTRY(UserProfile, "UserProfile", 100);

/**
 * @brief Custom converter implementation.
 *
 * To let fcf::convert know how to transform std::string into UserProfile,
 * we need to specialize the Converter template.
 */
namespace fcf {
  // Specialization for converting from std::string to UserProfile
  // Mode 3 (Mask: 0b00000011 )
  // The second bit (0b10) indicates that the Destination type is explicitly provided, not a template parameter
  // The first bit (0b01) indicates that the Source type is explicitly provided, not a template parameter
  template <>
  class Converter<3, UserProfile, std::string> {
    public:
    void operator()(UserProfile& a_destination, const std::string& a_source, ConvertOptions* /*a_options*/) {
      size_t delimiterPos = a_source.find(':');
      if (delimiterPos != std::string::npos) {
        try {
          a_destination.id = std::stoi(a_source.substr(0, delimiterPos));
          a_destination.username = a_source.substr(delimiterPos + 1);
        } catch (...) {
          throw fcf::ConvertFormatException(__FILE__, __LINE__, a_source, "UserProfile");
        }
      } else {
        throw fcf::ConvertFormatException(__FILE__, __LINE__, a_source, "UserProfile");
      }
    }
  };
}

int main() {
    std::cout << "=== [1] Built-in Conversions ===" << std::endl;
    {
        // Using fcf::convert to transform a string into an int
        // The conversion result is written into the first argument
        {
          std::string s = "42";
          int val;
          fcf::convert(val, s);
          std::cout << "String '" << s << "' converted to int: " << val << std::endl;
        }
        // Using fcf::convert to transform a string into a double. 
        // The conversion result is returned by the fcf::convert function
        {
          std::string s = "73.68";
          double val = fcf::convert<double>(s);
          std::cout << "String '" << s << "' converted to double: " << val << std::endl;
        }
    }

    std::cout << "\n=== [2] Conversion via fcf::Variant ===" << std::endl;
    {
        // A Variant can hold data, and we can extract it with automatic conversion
        fcf::Variant v = std::string("3.14");

        // The cast<T>() method inside Variant uses the fcf::convert system
        double d = v.cast<double>();

        std::cout << "Variant (string '3.14') cast to double: " << d << std::endl;
    }

    std::cout << "\n=== [3] Custom Converter (String -> UserProfile) ===" << std::endl;
    {
        std::string rawData = "101:CyberHekko178";
        UserProfile profile;

        // Calling our custom converter
        fcf::convert(profile, rawData);

        std::cout << "Parsed Profile -> ID: " << profile.id
                  << ", Name: " << profile.username << std::endl;
    }

    std::cout << "\n=== [4] Conversion Error Handling ===" << std::endl;
    {
        std::string badData = "not_a_number";
        int errorVal;

        try {
            // Attempting to convert an invalid string into an integer
            fcf::convert(errorVal, badData);
        } catch (const fcf::Exception& e) {
            std::cout << "Caught expected error: " << e.name() << std::endl;
            std::cout << "Message: " << e.message() << std::endl;
        }
    }

    return 0;
}