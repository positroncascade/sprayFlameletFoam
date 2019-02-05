{
    fvScalarMatrix ZEqn
    (
        fvm::ddt(rho, Z) + fvm::div(phi, Z)
      - fvm::laplacian(turbulence->muEff(), Z)
     == fvOptions(rho, Z)
      + parcels.SYi(0, Z) // Source term for YFuel
    );

    ZEqn.relax();

    fvOptions.constrain(ZEqn);

    ZEqn.solve();

    fvOptions.correct(Z);

    Info<< "Z min/max   " << min(Z).value() << ", "
        << max(Z).value() << endl;
}
