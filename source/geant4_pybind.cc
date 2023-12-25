#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eval.h>

#include <G4coutDestination.hh>
#include <G4UImanager.hh>
#include <G4LogicalVolumeStore.hh>
#include <G4LogicalVolume.hh>
#include <G4PhysicalVolumeStore.hh>
#include <G4VPhysicalVolume.hh>
#include <G4RegionStore.hh>
#include <G4Region.hh>
#include <G4SolidStore.hh>
#include <G4Material.hh>
#include <G4RunManager.hh>
#include <G4SurfaceProperty.hh>
#include <G4Version.hh>
#if G4VERSION_NUMBER < 1120
#include <G4strstreambuf.hh>
#endif

#include <cstdlib>
#include <vector>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class G4PyCoutDestination : public G4coutDestination {

public:
#if G4VERSION_NUMBER >= 1120
   G4int ReceiveG4debug(const G4String &msg) override
   {
      py::gil_scoped_acquire gil;
      auto                   pystdout = py::module_::import("sys").attr("stdout").attr("write");
      pystdout(msg);
      return 0;
   }
#endif

   G4int ReceiveG4cout(const G4String &msg) override
   {
      py::gil_scoped_acquire gil;
      auto                   pystdout = py::module_::import("sys").attr("stdout").attr("write");
      pystdout(msg);
      return 0;
   }

   G4int ReceiveG4cerr(const G4String &msg) override
   {
      py::gil_scoped_acquire gil;
      auto                   pystderr = py::module_::import("sys").attr("stderr").attr("write");
      pystderr(msg);
      return 0;
   }
};

class G4NullCoutDestination : public G4coutDestination {
public:
#if G4VERSION_NUMBER >= 1120
   G4int ReceiveG4debug(const G4String &) override { return 0; }
#endif
   G4int ReceiveG4cout(const G4String &) override { return 0; }
   G4int ReceiveG4cerr(const G4String &) override { return 0; }
};

static bool endsWith(const std::string &str, const std::string &end)
{
   if (str.length() >= end.length()) {
      return str.compare(str.length() - end.length(), end.length(), end) == 0;
   } else {
      return false;
   }
}

void export_modG4digit_hits(py::module &);
void export_modG4event(py::module &);
void export_modG4geometry(py::module &);
void export_modG4global(py::module &);
void export_modG4graphics_reps(py::module &);
void export_modG4intercoms(py::module &);
void export_modG4interface(py::module &);
void export_modG4materials(py::module &);
void export_modG4particles(py::module &);
void export_modG4physics_list(py::module &);
void export_modG4processes(py::module &);
void export_modG4run(py::module &);
void export_modG4tasking(py::module &);
void export_modG4track(py::module &);
void export_modG4tracking(py::module &);
void export_modG4visualization(py::module &);
void export_modG4persistency(py::module &);
void export_modG4analysis(py::module &);

PYBIND11_MODULE(geant4_pybind, m)
{
   export_modG4global(m);
   export_modG4intercoms(m);
   export_modG4graphics_reps(m);
   export_modG4digit_hits(m);
   export_modG4materials(m);
   export_modG4geometry(m);
   export_modG4particles(m);
   export_modG4processes(m);
   export_modG4track(m);
   export_modG4tracking(m);
   export_modG4event(m);
   export_modG4run(m);
   export_modG4tasking(m);
   export_modG4physics_list(m);
   export_modG4interface(m);
   export_modG4visualization(m);
   export_modG4persistency(m);
   export_modG4analysis(m);

   G4UImanager::GetUIpointer();
   static G4PyCoutDestination pycout = G4PyCoutDestination();
#if G4VERSION_NUMBER >= 1120
   G4iosSetDestination(&pycout);
#else
   G4coutbuf.SetDestination(&pycout);
   G4cerrbuf.SetDestination(&pycout);
#endif

   py::module_ atexit = py::module_::import("atexit");
   atexit.attr("register")(py::cpp_function([]() {
      py::gil_scoped_release gil_release;
      G4UImanager           *UImgr = G4UImanager::GetUIpointer();
      UImgr->SetCoutDestination(0);
      delete G4RunManager::GetRunManager();

      static G4NullCoutDestination nullcout = G4NullCoutDestination();
#if G4VERSION_NUMBER >= 1120
      G4iosSetDestination(&nullcout);
#else
      G4coutbuf.SetDestination(&nullcout);
      G4cerrbuf.SetDestination(&nullcout);
#endif

      // Delete everything before the interpreter shuts down to properly clean up python objects
      G4LogicalVolumeStore::Clean();
      G4LogicalVolume::Clean();
      G4RegionStore::Clean();
      G4Region::Clean();
      G4PhysicalVolumeStore::Clean();
      G4VPhysicalVolume::Clean();
      G4SolidStore::Clean();
      G4Material::GetMaterialTable()->clear();
      G4SurfaceProperty::CleanSurfacePropertyTable();
   }));

   py::dict modules = py::module_::import("sys").attr("modules");
   if (!modules["__main__"].attr("__dir__")().contains("__file__") ||
       !endsWith(modules["__main__"].attr("__file__").cast<std::string>(), "pybind11-stubgen")) {

      py::dict frameGlobals = py::globals();
      py::exec(
#include "datainit.py"
         , frameGlobals);

      py::dict envs = frameGlobals["envs_to_set"];

      static std::vector<std::string> variables;
      for (auto env : envs) {
         variables.emplace_back(env.first.cast<std::string>() + "=" + env.second.cast<std::string>());
         putenv(&variables.back()[0]);
      }
   }
}
