#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

FCF_EXCEPTION_DECLARE(CallNotFoundTestException, "FCF_CALL_NOT_FOUND_TEST", "Call '${{1}}$' not found with signature '${{2}}$'", 2);

namespace FcfTest {
  namespace BasisTest {

    FCF_TEST_DECLARE("fcfBasis", "Exception", "exception"){
      {
        std::string name, what,info;
        try {
          throw CallNotFoundTestException("Exception.cpp", 1, "call", "void*,void*");
        } catch(const fcf::Exception& e){
          name = e.name();
          what = e.what();
          info = e.info();
        }
        FCF_TEST(name == "FCF_CALL_NOT_FOUND_TEST", name);
        FCF_TEST(what == "Call 'call' not found with signature 'void*,void*'\nPosition: Exception.cpp:1", what);
        FCF_TEST(info == "Error:    FCF_CALL_NOT_FOUND_TEST\nMessage:  Call 'call' not found with signature 'void*,void*'\nPosition: Exception.cpp:1", info);
      }
      {
        std::string name, message,info, full;
        try {
          try {
            throw CallNotFoundTestException("Exception.cpp", 1, "call", "void*,void*");
          } catch(const fcf::Exception& e){
            throw CallNotFoundTestException(e, "Exception2.cpp", 2, "call2", "int");
          }
        } catch(const fcf::Exception& e){
          name = e.name();
          message = e.message();
          info = e.info();
          full = e.full();
        }
        FCF_TEST(name == "FCF_CALL_NOT_FOUND_TEST", name);
        FCF_TEST(message == "Call 'call2' not found with signature 'int'", message);
        FCF_TEST(info == "Error:    FCF_CALL_NOT_FOUND_TEST\nMessage:  Call 'call2' not found with signature 'int'\nPosition: Exception2.cpp:2", info);
        FCF_TEST(full == "Error:    FCF_CALL_NOT_FOUND_TEST\n"
                         "Message:  Call 'call2' not found with signature 'int'\n"
                         "Position: Exception2.cpp:2\n"
                         "Sub errors:\n"
                         "         1] Error:    FCF_CALL_NOT_FOUND_TEST\n"
                         "            Message:  Call 'call' not found with signature 'void*,void*'\n"
                         "            Position: Exception.cpp:1", full);
      }
    }

  } // namespace BasisTest
} // namespace FcfTest
