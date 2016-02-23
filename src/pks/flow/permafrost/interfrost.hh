/* -*-  mode: c++; c-default-style: "google"; indent-tabs-mode: nil -*- */

/*
  A base three-phase, thermal Richard's equation with water, water vapor, and
  ice for permafrost applications.

  Note that the only difference between permafrost and richards is in
  constitutive relations -- the WRM changes to provide three saturations,
  while the water content changes to account for water in ice phase.  As these
  are now drop-in field evaluators, there is very little to change in the PK.

  License: BSD
  Authors: Ethan Coon (ATS version) (ecoon@lanl.gov)
*/

#ifndef PK_FLOW_INTERFROST_HH_
#define PK_FLOW_INTERFROST_HH_

#include "Teuchos_RCP.hpp"
#include "Teuchos_ParameterList.hpp"

#include "CompositeVector.hh"
#include "TreeVector.hh"
#include "State.hh"
#include "upwinding.hh"
#include "boundary_function.hh"

#include "pk.hh"
#include "pk_factory.hh"

#include "permafrost.hh"

namespace Amanzi {
namespace Flow {

class Interfrost : public Permafrost {

public:
  // Constructors.
  Interfrost(const Teuchos::RCP<Teuchos::ParameterList>& plist,
             Teuchos::ParameterList& FElist,
             const Teuchos::RCP<TreeVector>& solution) :
      PKDefaultBase(plist, FElist, solution),
      Permafrost(plist, FElist, solution) {}

  // Virtual destructor
  virtual ~Interfrost() {}

  // -- accumulation term
  virtual void UpdatePreconditioner(double t,
          Teuchos::RCP<const TreeVector> up, double h);

protected:
  virtual void AddAccumulation_(const Teuchos::Ptr<CompositeVector>& g);

  // Create of physical evaluators.
  virtual void SetupPhysicalEvaluators_(const Teuchos::Ptr<State>& S);

private:
  // factory registration
  static RegisteredPKFactory<Interfrost> reg_;

};

}  // namespace AmanziFlow
}  // namespace Amanzi

#endif
