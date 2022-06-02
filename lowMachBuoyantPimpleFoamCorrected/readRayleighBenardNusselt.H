// Only useful if reader wants to assess Rayleigh-Benard Nusselt number

Info<< "Reading flowProperties\n" << endl;

IOdictionary flowProperties
(
    IOobject
    (
        "flowProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);

dimensionedScalar TRef
(
    "TRef",
    dimTemperature,
    flowProperties
);

dimensionedScalar deltaTRef
(
    "deltaTRef",
    dimTemperature,
    flowProperties
);

dimensionedScalar rhoRef
(
    "rhoRef",
    dimDensity,
    flowProperties
);

dimensionedScalar URef
(
    "URef",
    dimVelocity,
    flowProperties
);


dimensionedScalar RaRef
(
    "RaRef",
    dimless,
    flowProperties
);

dimensionedScalar PrRef
(
    "PrRef",
    dimless,
    flowProperties
);

Info<< "Creating field nonDimT\n" << endl;
volScalarField nonDimT
(
    IOobject
    (
        "nonDimT",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Creating field nonDimRho\n" << endl;
volScalarField nonDimRho
(
    IOobject
    (
        "nonDimRho",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "\nReading field nonDimU\n" << endl;
volVectorField nonDimU
(
    IOobject
    (
        "nonDimU",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Creating field nusseltOne\n" << endl;
volScalarField nusseltOne
(
    IOobject
    (
        "nusseltOne",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Creating field nusseltTwo\n" << endl;
volScalarField nusseltTwo
(
    IOobject
    (
        "nusseltTwo",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Creating field nusseltTotal\n" << endl;
volScalarField nusseltTotal
(
    IOobject
    (
        "nusseltTotal",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
