Unit Testing Property Types
===========================

Conceptually each property type is an abstract base class. The actual
`PropertyType` class is unit tested in pluginplay and does not need to be tested here
again. What we need to test are the derived classes, which define the property
types modules can choose from. For the most part these derived classes do not
do anything aside from define meta data. Thus these unit tests do not do much
beyond asserting that the property types compile and are usable.

By convention all unit tests in this repo simply loop over the input and result
fields and assert that they exist in the input/results that are returned by
the `inputs`/`results` functions of the property type. To aid in this endeavor,
the `test_property_type.hpp` header file defines a function `test_property_type`
that takes the type of the property type to test, an initializer list containing
the input fields, and an initializer list containing the result fields. As an
example, for the `CoulombMatrix` property type this looks like:

```
TEST_CASE("CoulombMatrix"){
    test_property_type<CoulombMatrix<>>(
        {"Molecule", "Molecular Orbitals", "Bra", "Ket", "Derivative"},
        ("Coulomb Matrix"}
    );
}
```
