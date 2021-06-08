#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PhysicalConstants.hh>

namespace py = pybind11;

void export_G4PhysicalConstants(py::module &m)
{
   m.attr("alpha_rcl2")              = alpha_rcl2;
   m.attr("amu")                     = amu;
   m.attr("amu_c2")                  = amu_c2;
   m.attr("Avogadro")                = Avogadro;
   m.attr("Bohr_radius")             = Bohr_radius;
   m.attr("c_light")                 = c_light;
   m.attr("c_squared")               = c_squared;
   m.attr("classic_electr_radius")   = classic_electr_radius;
   m.attr("e_squared")               = e_squared;
   m.attr("electron_charge")         = electron_charge;
   m.attr("electron_Compton_length") = electron_Compton_length;
   m.attr("electron_mass_c2")        = electron_mass_c2;
   m.attr("elm_coupling")            = elm_coupling;
   m.attr("epsilon0")                = epsilon0;
   m.attr("fine_structure_const")    = fine_structure_const;
   m.attr("h_Planck")                = h_Planck;
   m.attr("halfpi")                  = halfpi;
   m.attr("hbar_Planck")             = hbar_Planck;
   m.attr("hbarc")                   = hbarc;
   m.attr("hbarc_squared")           = hbarc_squared;
   m.attr("k_Boltzmann")             = k_Boltzmann;
   m.attr("kGasThreshold")           = kGasThreshold;
   m.attr("mu0")                     = mu0;
   m.attr("neutron_mass_c2")         = neutron_mass_c2;
   m.attr("pi")                      = pi;
   m.attr("pi2")                     = pi2;
   m.attr("proton_mass_c2")          = proton_mass_c2;
   m.attr("STP_Pressure")            = STP_Pressure;
   m.attr("STP_Temperature")         = STP_Temperature;
   m.attr("twopi")                   = twopi;
   m.attr("twopi_mc2_rcl2")          = twopi_mc2_rcl2;
   m.attr("universe_mean_density")   = universe_mean_density;
}
