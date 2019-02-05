{
    fvScalarMatrix rhoEqn
    (
        fvm::ddt(rho)
      + fvc::div(phi)
      ==
        parcels.Srho(rho)
      + fvOptions(rho)
    );

    rhoEqn.solve();

    fvOptions.correct(rho);
}
