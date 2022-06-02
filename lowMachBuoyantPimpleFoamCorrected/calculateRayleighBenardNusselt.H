// To calculate the Nusselt number in RBC in a cube

nonDimU = (U/URef); 
nonDimRho = (rho/rhoRef); 
nonDimT = (T-TRef)/(deltaTRef); 

volVectorField gradNonDimT(fvc::grad(nonDimT));

volScalarField gradNonDimTy
(
    IOobject
    (
        "gradNonDimTy",
        runTime.timeName(),
        mesh
    ),
    gradNonDimT.component(vector::Y)
);

volScalarField nonDimUy
(
    IOobject
    (
        "nonDimUy",
        runTime.timeName(),
        mesh
    ),
    nonDimU.component(vector::Y)
);

nusseltOne = sqrt(RaRef*PrRef)*nonDimUy*nonDimRho*nonDimT;
nusseltTwo = hRef*gradNonDimTy; // hRef is to nonDimensionalize the denominator in grad term
nusseltTotal = nusseltOne - nusseltTwo;
