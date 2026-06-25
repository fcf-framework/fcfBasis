#define FCF_BASIS_IMPLEMENTATION
#include <fcfBasis/basis.hpp>

struct Person {
    int age;
    std::string name;
};

FCF_TYPE_REGISTRATION(Person, "Person", 0);

// Type specialization for LessSpecifier
namespace fcf {
    template<>
    struct Type<Person, LessSpecifier> : public TypeImpl<Person, LessSpecifier> {
        inline bool call(const Person* a_left, const Person* a_right) const {
            return a_left->age < a_right->age;
        }
    };
}

// Specifier Registration
FCF_SPECIFIER_REGISTRATION(Person, fcf::LessSpecifier);

int main() {
    Person p1{25, "Alice"};
    Person p2{30, "Bob"};

    fcf::Variant vp1(p1);
    fcf::Variant vp2(p2);

    // Variant comparison uses LessSpecifier
    if (vp1 < vp2) {
        std::cout << "Alice is younger than Bob" << std::endl;
    }
    return 0;
}
