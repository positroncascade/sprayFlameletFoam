{
    fvScalarMatrix ZEqn
    (
        fvm::ddt(rho, Z) + fvm::div(phi, Z)
      - fvm::laplacian(turbulence->alphaEff(), Z)
     == fvOptions(rho, Z)
    );

    ZEqn.relax();

    fvOptions.constrain(ZEqn);

    ZEqn.solve();

    fvOptions.correct(Z);

    Info<< "Z min/max   " << min(Z).value() << ", "
        << max(Z).value() << endl;
}
