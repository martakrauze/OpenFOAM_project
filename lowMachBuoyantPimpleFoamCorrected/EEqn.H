{
    volScalarField& h = thermo.he();

    fvScalarMatrix EEqn
    (
        fvm::ddt(rho, h) + fvm::div(phi, h)
      -  dpdt
      - fvm::laplacian(turbulence->alphaEff(), h)
     ==
      fvOptions(rho, h)
    );

    EEqn.relax();

    fvOptions.constrain(EEqn);

    EEqn.solve();

    fvOptions.correct(h);

    thermo.correct();

    Info<< "min/max(T) = "
        << min(T).value() << ", " << max(T).value() << endl;
}
