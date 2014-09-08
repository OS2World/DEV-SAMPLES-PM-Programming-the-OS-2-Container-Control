/*  This function filters out either Gas-Powered or Manual vehicles
 *  depending on the given return values in FILTERSTRUCT.
 *  Using the bGasPowered field of VEHICLERECORD to distinguish. */
BOOL  EXPENTRY pfnFilter(PRECORDCORE preccObj, PVOID pStorage)
{
  if (((PVEHICLERECORD)preccObj)->bGasPowered)
    return ((PFILTERSTRUCT)pStorage)->RetVal1;
  else
    return ((PFILTERSTRUCT)pStorage)->RetVal2;
}
