#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4OpticalSurface.hh>
#include <G4MaterialPropertiesTable.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4OpticalSurface : public G4OpticalSurface, public py::trampoline_self_life_support {
public:
   using G4OpticalSurface::G4OpticalSurface;

   void SetType(const G4SurfaceType &type) override { PYBIND11_OVERRIDE(void, G4OpticalSurface, SetType, type); }
};

void export_G4OpticalSurface(py::module &m)
{
   py::enum_<G4OpticalSurfaceFinish>(m, "G4OpticalSurfaceFinish")
      .value("polished", polished)
      .value("polishedfrontpainted", polishedfrontpainted)
      .value("polishedbackpainted", polishedbackpainted)
      .value("ground", ground)
      .value("groundfrontpainted", groundfrontpainted)
      .value("groundbackpainted", groundbackpainted)
      .value("polishedlumirrorair", polishedlumirrorair)
      .value("polishedlumirrorglue", polishedlumirrorglue)
      .value("polishedair", polishedair)
      .value("polishedteflonair", polishedteflonair)
      .value("polishedtioair", polishedtioair)
      .value("polishedtyvekair", polishedtyvekair)
      .value("polishedvm2000air", polishedvm2000air)
      .value("polishedvm2000glue", polishedvm2000glue)
      .value("etchedlumirrorair", etchedlumirrorair)
      .value("etchedlumirrorglue", etchedlumirrorglue)
      .value("etchedair", etchedair)
      .value("etchedteflonair", etchedteflonair)
      .value("etchedtioair", etchedtioair)
      .value("etchedtyvekair", etchedtyvekair)
      .value("etchedvm2000air", etchedvm2000air)
      .value("etchedvm2000glue", etchedvm2000glue)
      .value("groundlumirrorair", groundlumirrorair)
      .value("groundlumirrorglue", groundlumirrorglue)
      .value("groundair", groundair)
      .value("groundteflonair", groundteflonair)
      .value("groundtioair", groundtioair)
      .value("groundtyvekair", groundtyvekair)
      .value("groundvm2000air", groundvm2000air)
      .value("groundvm2000glue", groundvm2000glue)
      .value("Rough_LUT", Rough_LUT)
      .value("RoughTeflon_LUT", RoughTeflon_LUT)
      .value("RoughESR_LUT", RoughESR_LUT)
      .value("RoughESRGrease_LUT", RoughESRGrease_LUT)
      .value("Polished_LUT", Polished_LUT)
      .value("PolishedTeflon_LUT", PolishedTeflon_LUT)
      .value("PolishedESR_LUT", PolishedESR_LUT)
      .value("PolishedESRGrease_LUT", PolishedESRGrease_LUT)
      .value("Detector_LUT", Detector_LUT)
      .export_values();

   py::enum_<G4OpticalSurfaceModel>(m, "G4OpticalSurfaceModel")
      .value("glisur", glisur)
      .value("unified", unified)
      .value("LUT", LUT)
      .value("DAVIS", DAVIS)
      .value("dichroic", dichroic)
      .export_values();

   py::class_<G4OpticalSurface, PyG4OpticalSurface, G4SurfaceProperty, py::nodelete>(m, "G4OpticalSurface")

      .def("__copy__", [](const PyG4OpticalSurface &self) { return new PyG4OpticalSurface(self); })
      .def("__deepcopy__", [](const PyG4OpticalSurface &self, py::dict) { return new PyG4OpticalSurface(self); })
      .def("__copy__", [](const G4OpticalSurface &self) { return new G4OpticalSurface(self); })
      .def("__deepcopy__", [](const G4OpticalSurface &self, py::dict) { return new G4OpticalSurface(self); })
      .def(py::init<const G4String &, G4OpticalSurfaceModel, G4OpticalSurfaceFinish, G4SurfaceType, G4double>(),
           py::arg("name"), py::arg("model") = glisur, py::arg("finish") = polished,
           py::arg("type") = dielectric_dielectric, py::arg("value") = 1.)

      .def("DumpInfo", &G4OpticalSurface::DumpInfo)
      .def("GetAngularDistributionValue", &G4OpticalSurface::GetAngularDistributionValue)
      .def("GetAngularDistributionValueLUT", &G4OpticalSurface::GetAngularDistributionValueLUT)
      .def("GetDichroicVector", &G4OpticalSurface::GetDichroicVector, py::return_value_policy::reference)
      .def("GetFinish", &G4OpticalSurface::GetFinish)
      .def("GetInmax", &G4OpticalSurface::GetInmax)
      .def("GetLUTbins", &G4OpticalSurface::GetLUTbins)
      .def("GetMaterialPropertiesTable", &G4OpticalSurface::GetMaterialPropertiesTable,
           py::return_value_policy::reference)

      .def("GetModel", &G4OpticalSurface::GetModel)
      .def("GetPhiIndexMax", &G4OpticalSurface::GetPhiIndexMax)
      .def("GetPolish", &G4OpticalSurface::GetPolish)
      .def("GetRefMax", &G4OpticalSurface::GetRefMax)
      .def("GetReflectivityLUTValue", &G4OpticalSurface::GetReflectivityLUTValue)
      .def("GetSigmaAlpha", &G4OpticalSurface::GetSigmaAlpha)
      .def("GetThetaIndexMax", &G4OpticalSurface::GetThetaIndexMax)
      .def("ReadCompressedFile", &G4OpticalSurface::ReadCompressedFile)
      .def("ReadDataFile", &G4OpticalSurface::ReadDataFile)
      .def("ReadDichroicFile", &G4OpticalSurface::ReadDichroicFile)
      .def("ReadLUTDAVISFile", &G4OpticalSurface::ReadLUTDAVISFile)
      .def("ReadLUTFile", &G4OpticalSurface::ReadLUTFile)
      .def("ReadReflectivityLUTFile", &G4OpticalSurface::ReadReflectivityLUTFile)
      .def("SetFinish", &G4OpticalSurface::SetFinish)
      .def(
         "SetMaterialPropertiesTable",
         [](G4OpticalSurface &self, py::disown_ptr<G4MaterialPropertiesTable> anMPT) {
            self.SetMaterialPropertiesTable(anMPT);
         },
         py::arg("anMPT"))

      .def("SetModel", &G4OpticalSurface::SetModel, py::arg("model"))
      .def("SetPolish", &G4OpticalSurface::SetPolish, py::arg("plsh"))
      .def("SetSigmaAlpha", &G4OpticalSurface::SetSigmaAlpha, py::arg("s_a"))
      .def("SetType", &G4OpticalSurface::SetType, py::arg("type"))
      .def(py::self != py::self)
      .def(py::self == py::self);
}
