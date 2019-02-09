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
    const int kIndex = 2;
    volScalarField& tY = Y[kIndex];
    fvScalarMatrix YEqn
    (
        fvm::ddt(rho, tY) + mvConvection->fvmDiv(phi, tY)
      - fvm::laplacian(turbulence->alphaEff(), tY)
     ==
        fvOptions(rho, tY)
      + parcels.SYi(kIndex, tY)
    );

    YEqn.relax();
    
    fvOptions.constrain(YEqn);

    YEqn.solve(mesh.solver("Yi"));

    fvOptions.correct(tY);

    tY.max(0.0);

    Z = scalar(1) - tY/0.766;
    Info<< "Z min/max   " << min(Z).value() << ", "
        << max(Z).value() << endl;
}
