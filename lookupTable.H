{
    // Energy
    volScalarField& he = thermo.he();
    forAll(Z.internalField(), i)
    {
        if(Z[i] < 0.0621) T[i] = 25764.9*Z[i] + 800;
        else T[i] = -1705.94*Z[i] + 1705.94 + 800;
    }
    he = thermo.he(p,T);
    thermo.correct();
    Info<< "T gas min/max   " << min(T).value() << ", "
        << max(T).value() << endl;
}