void lookupTable(const volScalarField& Z, volScalarField& T)
{
    forAll(Z, i)
    {
        if(Z[i] < 0.0621) T[i] = 25764.9*Z[i] + 800;
        else T[i] = -1705.94*Z[i] + 1705.94 + 800;
    }
}