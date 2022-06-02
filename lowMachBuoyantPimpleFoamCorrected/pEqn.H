psi = thermo.psi();
p = totalMass0/fvc::domainIntegrate(psi);
rho = thermo.rho();

dimensionedScalar totalMass = fvc::domainIntegrate(rho);
scalar constantMass = (totalMass0/totalMass).value();

Info<< "Should be constant in time  " << constantMass << endl;

    Info<< "min/max(rho) = "
        << min(rho).value() << ", " << max(rho).value() << endl;

    Info<< "min/max(psi) = "
        << min(psi).value() << ", " << max(psi).value() << endl;

    Info<< "min/max(p) = "
        << min(p).value() << ", " << max(p).value() << endl;

volScalarField rAU(1.0/UEqn.A());
surfaceScalarField rhorAUf("rhorAUf", fvc::interpolate(rho*rAU));
volVectorField HbyA(constrainHbyA(rAU*UEqn.H(), U, p)); // to pd or not to pd ?
surfaceScalarField phig("phig", -rhorAUf*ghf*fvc::snGrad(rho)*mesh.magSf());

surfaceScalarField phiHbyA
(
    "phiHbyA",
    (
        fvc::flux(rho*HbyA)
    )
    + phig
);

constrainPressure(pd, rho, U, phiHbyA, rhorAUf);

while (pimple.correctNonOrthogonal())
{
    fvScalarMatrix pdEqn
    (
        fvm::ddt(psi, pd)
      - fvc::ddt(psi, pd)
      + fvc::ddt(psi)*p
      + fvc::div(phiHbyA)
      - fvm::laplacian(rhorAUf, pd)
     ==
        fvOptions(psi, pd, rho.name())
    );

    pdEqn.solve(mesh.solver(pd.select(pimple.finalInnerIter())));

    if (pimple.finalNonOrthogonalIter())
    {
        phi = phiHbyA + pdEqn.flux();
        U = HbyA + rAU*fvc::reconstruct((pdEqn.flux() + phig)/rhorAUf);
        U.correctBoundaryConditions();
        fvOptions.correct(U);
    }
}

#include "rhoEqn.H"
#include "compressibleContinuityErrs.H"

if (thermo.dpdt())
{
    dpdt = fvc::ddt(p);
}

#include "calculateRayleighBenardNusselt.H"
