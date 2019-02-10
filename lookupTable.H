{
    // Infinitely Fast Chemistry
    
    // Species
    forAll(Z.internalField(), i)
    {
        if(Z[i] < 0.0621)
        {
            Y[0][i] = 0;
            Y[1][i] = -3.7681159420289854*Z[i] + 0.234;
            // Y[2][i] = -12.334943639291465*Z[i] + 0.766;
            Y[3][i] = 3.0896188277542653*Z[i];
            Y[4][i] = 1.44449711427472*Z[i];
        }
        else
        {
            Y[0][i] = 1.0662117496534813*Z[i] - 0.06621174965348119;
            Y[1][i] = 0;
            // Y[2][i] = 0;
            Y[3][i] = -0.2045690683479474*Z[i] + 0.2045690683479474;
            Y[4][i] = -0.09564268130553377*Z[i] + 0.09564268130553377;
        }
    }

    // Energy
    volScalarField& he = thermo.he();
    forAll(Z.internalField(), i)
    {
        if(Z[i] < 0.0621) T[i] = 25764.9*Z[i] + 800;
        else T[i] = -1705.94*Z[i] + 1705.94 + 800;
    }
    he = thermo.he(p,T);
    thermo.correct();
    Info<< "T gas min/max : " << min(T).value() << ", "
        << max(T).value() << endl;
}