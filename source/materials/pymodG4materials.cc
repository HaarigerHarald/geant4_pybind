#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define EXPORT_G4HEADER(header, mod)   \
   void export_##header(py::module &); \
   export_##header(mod)

void export_modG4materials(py::module &m)
{
   EXPORT_G4HEADER(G4VMaterialExtension, m);
   EXPORT_G4HEADER(G4VIonDEDXTable, m);

   EXPORT_G4HEADER(G4Material, m);
   EXPORT_G4HEADER(G4ExtendedMaterial, m);

   EXPORT_G4HEADER(G4SurfaceProperty, m);
   EXPORT_G4HEADER(G4OpticalSurface, m);

   EXPORT_G4HEADER(G4AtomicBond, m);
   EXPORT_G4HEADER(G4AtomicFormFactor, m);
   EXPORT_G4HEADER(G4AtomicShells_XDB_EADL, m);
   EXPORT_G4HEADER(G4AtomicShells, m);
   EXPORT_G4HEADER(G4CrystalAtomBase, m);
   EXPORT_G4HEADER(G4CrystalExtension, m);
   EXPORT_G4HEADER(G4CrystalUnitCell, m);
   EXPORT_G4HEADER(G4DensityEffectCalculator, m);
   EXPORT_G4HEADER(G4DensityEffectData, m);

   EXPORT_G4HEADER(G4ElementTable, m);
   EXPORT_G4HEADER(G4Element, m);
   EXPORT_G4HEADER(G4ElementData, m);

   EXPORT_G4HEADER(G4ExtDEDXTable, m);
   EXPORT_G4HEADER(G4ICRU90StoppingData, m);
   EXPORT_G4HEADER(G4IonisParamElm, m);
   EXPORT_G4HEADER(G4IonisParamMat, m);
   EXPORT_G4HEADER(G4IonStoppingData, m);
   EXPORT_G4HEADER(G4Isotope, m);
   EXPORT_G4HEADER(G4LatticeLogical, m);
   EXPORT_G4HEADER(G4LatticePhysical, m);
   EXPORT_G4HEADER(G4MaterialPropertiesIndex, m);
   EXPORT_G4HEADER(G4MaterialPropertiesTable, m);
   EXPORT_G4HEADER(G4MaterialTable, m);
   EXPORT_G4HEADER(G4MicroElecMaterialStructure, m);
   EXPORT_G4HEADER(G4MicroElecSiStructure, m);
   EXPORT_G4HEADER(G4NistElementBuilder, m);
   EXPORT_G4HEADER(G4NistManager, m);
   EXPORT_G4HEADER(G4NistMaterialBuilder, m);
   EXPORT_G4HEADER(G4NistMessenger, m);
   EXPORT_G4HEADER(G4OpticalMaterialProperties, m);
   EXPORT_G4HEADER(G4SandiaTable, m);
   EXPORT_G4HEADER(G4UCNMaterialPropertiesTable, m);
   EXPORT_G4HEADER(G4UCNMicroRoughnessHelper, m);
}
