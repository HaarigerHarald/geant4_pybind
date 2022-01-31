## Introduction

It will be assumed that you already gained some experience with C++ development as well as geant4 and familiarized yourself with the [pybind11 documentation](https://pybind11.readthedocs.io/en/latest).

## smart_holder

A limitation of pybind11's master branch is that it cannot properly handle the complex ownership model of geant4. As an example `G4RunManager` takes ownership of an object derived from `G4VUserDetectorConstruction`, in Python, this would mean that not only the underlying "wrapper" or "trampoline" object's ownership is transferred, but also that the Python object must be kept alive until `G4RunManager` decides to destruct the "wrapper", otherwise callbacks into the Python object from C++ would fail.

For such complex ownership transfers, the pybind11 [smart_holder](https://github.com/pybind/pybind11/tree/smart_holder) branch was created. By using a smart_holder, casts to and from `unique_ptr` and `shared_ptr` will properly transfer ownership.

### disown_ptr

This is all great, however geant4 dates back to before C++11 was created and so a lot of ownership transfers happen with raw pointers. For this reason, `disown_ptr` was added, whose sole purpose is to reflect ownership transfer without losing access to the object like `unique_ptr` would.

The binding for the ownership transfer mentioned above would thus look like:

```cpp
g4RunManager.def("SetUserInitialization",
    [](G4RunManager &self,
    py::disown_ptr<G4VUserDetectorConstruction> detector) {
        self.SetUserInitialization(detector);
    });
```

### nodelete

One slight peculiarity of geant4 is that there are certain objects that implicitly get disowned on construction and added to some global store (i.e. Solids, LogicalVolumes, PhysicalVolumes). To tell pybind11 that the object needs to be constructed in a non-owning way you should specify `nodelete` as a template argument of the `class_` function.

```cpp
py::class_<G4Box, PyG4Box, G4CSGSolid, py::nodelete> g4box(m, "G4Box");
```

## G4String

Python strings will be automatically cast from and to G4Strings. You can therefore ignore the G4String class altogether.

## Includes

The following includes should be present in each compilation unit.

```cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh" // disown_ptr and G4String typecasters
#include "opaques.hh" // all opaque declarations
```

## TLDR

* Include:
    ```cpp
    #include <pybind11/pybind11.h>
    #include <pybind11/stl.h>

    #include "typecast.hh"
    #include "opaques.hh"
    ```

* Wrap functions that disown a raw pointer with a lambda that uses a `disown_ptr` argument instead of its raw pointer equivalent.

* Add `nodelete` to pybind11's `class_` template arguments if the object is disowned on construction (i.e. added to some global store).
