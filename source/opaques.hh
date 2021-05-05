#ifndef OPAQUES_HH
#define OPAQUES_HH

#include <pybind11/pybind11.h>

#include <G4MaterialTable.hh>
#include <G4ElementTable.hh>
#include <G4Isotope.hh>

#include <G4VProcess.hh>
#include <G4UnitsTable.hh>
#include <G4TrajectoryContainer.hh>

#include <G4ThreeVector.hh>
#include <G4TwoVector.hh>

PYBIND11_MAKE_OPAQUE(G4MaterialTable);
PYBIND11_MAKE_OPAQUE(G4ElementTable);
PYBIND11_MAKE_OPAQUE(G4IsotopeTable);

typedef std::vector<G4VProcess *> G4ProcVector;

PYBIND11_MAKE_OPAQUE(G4ProcVector);

PYBIND11_MAKE_OPAQUE(G4UnitsTable);
PYBIND11_MAKE_OPAQUE(G4UnitsContainer);

PYBIND11_MAKE_OPAQUE(TrajectoryVector);

typedef std::vector<G4int>         G4intVector;
typedef std::vector<G4double>      G4doubleVector;
typedef std::vector<G4String>      G4StringVector;
typedef std::vector<G4ThreeVector> G4ThreeVectorVector;
typedef std::vector<G4TwoVector>   G4TwoVectorVector;

PYBIND11_MAKE_OPAQUE(G4intVector);
PYBIND11_MAKE_OPAQUE(G4doubleVector);
PYBIND11_MAKE_OPAQUE(G4StringVector);
PYBIND11_MAKE_OPAQUE(G4ThreeVectorVector);
PYBIND11_MAKE_OPAQUE(G4TwoVectorVector);

#endif // OPAQUES_HH
