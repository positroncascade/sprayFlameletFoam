tmp<fv::convectionScheme<scalar>> mvConvection
(
    fv::convectionScheme<scalar>::New
    (
       mesh,
       fields,
       phi,
       mesh.divScheme("div(phi,Yi_h)")
    )
);

{
    volScalarField& inY = Y[inertIndex];
    fvScalarMatrix YEqn
    (
        fvm::ddt(rho, inY) + mvConvection->fvmDiv(phi, inY)
      - fvm::laplacian(turbulence->muEff(), inY)
     ==
        fvOptions(rho, inY)
      + parcels.SYi(inertIndex, inY)
    );

    YEqn.relax();
    
    fvOptions.constrain(YEqn);

    YEqn.solve(mesh.solver("Yi"));

    fvOptions.correct(inY);

    inY.max(0.0);

    Z = scalar(1) - inY/0.0138;
    Info<< "Z min/max : " << min(Z).value() << ", "
        << max(Z).value() << endl;
}
