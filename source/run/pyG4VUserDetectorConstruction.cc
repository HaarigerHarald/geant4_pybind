#include <pybind11/pybind11.h>

#include <G4VUserDetectorConstruction.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VUserParallelWorld.hh>
#include <G4VSensitiveDetector.hh>
#include <G4LogicalVolume.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

class PublicG4VUserDetectorConstruction : public G4VUserDetectorConstruction {

public:
   using G4VUserDetectorConstruction::G4VUserDetectorConstruction;
   using G4VUserDetectorConstruction::SetSensitiveDetector;
};

class TRAMPOLINE_NAME(G4VUserDetectorConstruction) : public G4VUserDetectorConstruction {

public:
   using G4VUserDetectorConstruction::G4VUserDetectorConstruction;

   G4VPhysicalVolume *Construct() override
   {
      py::gil_scoped_acquire gil;
      py::function override = py::get_override(static_cast<const G4VUserDetectorConstruction *>(this), "Construct");
      if (override) {
         py::object o = override();
         py::handle pySelf =
            py::cast(static_cast<const G4VUserDetectorConstruction *>(this), py::return_value_policy::reference);

         if (pySelf && o && !pySelf.is_none() && !o.is_none()) {
            py::detail::add_patient(pySelf.ptr(), o.ptr());
         }
         if (py::detail::cast_is_temporary_value_reference<G4VPhysicalVolume *>::value) {
            static py::detail::override_caster_t<G4VPhysicalVolume *> caster;
            return py::detail::cast_ref<G4VPhysicalVolume *>(std::move(o), caster);
         } else
            return py::detail::cast_safe<G4VPhysicalVolume *>(std::move(o));
      }

      py::pybind11_fail("Tried to call pure virtual function \"G4VUserDetectorConstruction::Construct\"");
   }

   void ConstructSDandField() override { PYBIND11_OVERRIDE(void, G4VUserDetectorConstruction, ConstructSDandField, ); }

   void CloneSD() override { PYBIND11_OVERRIDE(void, G4VUserDetectorConstruction, CloneSD, ); }

   void CloneF() override { PYBIND11_OVERRIDE(void, G4VUserDetectorConstruction, CloneF, ); }

   TRAMPOLINE_DESTRUCTOR(G4VUserDetectorConstruction);
};

void export_G4VUserDetectorConstruction(py::module &m)
{
   py::class_<G4VUserDetectorConstruction, TRAMPOLINE_NAME(G4VUserDetectorConstruction),
              owntrans_ptr<G4VUserDetectorConstruction>>(m, "G4VUserDetectorConstruction",
                                                         "base class of user detector construction")

      .def(py::init<>())
      .def("Construct", &G4VUserDetectorConstruction::Construct)
      .def("ConstructSDandField", &G4VUserDetectorConstruction::ConstructSDandField)
      .def("GetNumberOfParallelWorld", &G4VUserDetectorConstruction::GetNumberOfParallelWorld)
      .def("ConstructParallelGeometries", &G4VUserDetectorConstruction::ConstructParallelGeometries)
      .def("ConstructParallelSD", &G4VUserDetectorConstruction::ConstructParallelSD)

      .def("CloneSD", &G4VUserDetectorConstruction::CloneSD)
      .def("CloneF", &G4VUserDetectorConstruction::CloneF)
      .def("RegisterParallelWorld", &G4VUserDetectorConstruction::RegisterParallelWorld)
      .def("GetParallelWorld", &G4VUserDetectorConstruction::GetParallelWorld)

      .def("SetSensitiveDetector",
           static_cast<void (G4VUserDetectorConstruction::*)(const G4String &, G4VSensitiveDetector *, G4bool)>(
              &PublicG4VUserDetectorConstruction::SetSensitiveDetector),
           py::arg("logVolName"), py::arg("aSD"), py::arg("multi") = false, py::keep_alive<1, 3>())

      .def("SetSensitiveDetector",
           static_cast<void (G4VUserDetectorConstruction::*)(G4LogicalVolume *, G4VSensitiveDetector *)>(
              &PublicG4VUserDetectorConstruction::SetSensitiveDetector),
           py::keep_alive<1, 3>());
}
