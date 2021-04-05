#ifndef MATERIAL_OPAQUE_TYPES_HH
#define MATERIAL_OPAQUE_TYPES_HH

#include <pybind11/pybind11.h>

#include <G4MaterialTable.hh>
#include <G4ElementTable.hh>
#include <G4Isotope.hh>

PYBIND11_MAKE_OPAQUE(G4MaterialTable);
PYBIND11_MAKE_OPAQUE(G4ElementTable);
PYBIND11_MAKE_OPAQUE(G4IsotopeTable);

#endif //MATERIAL_OPAQUE_TYPES_HH
