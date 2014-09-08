/* User defined record structure.  Contains RECORDCORE plus
 * application specific fields. */
typedef struct _VEHICLERECORD {
   RECORDCORE   RecordCore;
   PSZ          Year;              /* Year of manufacture             */
   PSZ          Vehicle;           /* Make and Model                  */
   ULONG        Price;             /* Current Value in U.S. Dollars   */
   PSZ          Color;             /* Dominant Color                  */
   ULONG        MPG;               /* Miles Per Gallon                */
   ULONG        CalPerHr;          /* Calories Per Hour               */
   ULONG        Mileage;           /* Current Mileage                 */
   BOOL         bGasPowered;       /* TRUE->Gas Powered, FALSE->Manual*/
} VEHICLERECORD, *PVEHICLERECORD;

/* Structure definition to set up return values for filter function */
typedef struct _FILTERSTRUCT {
   BOOL         RetVal1;
   BOOL         RetVal2;
} FILTERSTRUCT, *PFILTERSTRUCT;

  /* The User wants a subset of the container items.(Process Filtering)
   * This code would be called as a result of the user selecting menu
   * options. */
  case CNR_FILTER_GASPOWERED:
  case CNR_FILTER_MANUAL:
    {
      PFIELDINFO     pFieldInfo;
      FILTERSTRUCT   FilterStruct;

      /* Setup Return values.  TRUE->Visible, FALSE->NOT Visible
       * This is so filter function knows whether to filter out
       * Gas Powered objects or Manual Powered objects.
       * Thus, we don't need two separate filter functions. */
      if (SHORT1FROMMP(mp1) == CNR_FILTER_GASPOWERED)
      {
        FilterStruct.RetVal1 = TRUE;
        FilterStruct.RetVal2 = FALSE;
      }
      else
      {
        FilterStruct.RetVal1 = FALSE;
        FilterStruct.RetVal2 = TRUE;
      }

      /* Tell the container to start the Filtering Process. */
      WinSendMsg (hwndCnr, CM_FILTER,
                  MPFROMP(pfnFilter), MPFROMP(&FilterStruct));

      /* Obtain pointer to the first Details View Column */
      pFieldInfo = (PFIELDINFO)WinSendMsg (hwndCnr, CM_QUERYDETAILFIELDINFO,
                                           NULL, MPFROMSHORT(CMA_FIRST));

      /* Iterate through all columns and make visible only those
       * columns that apply to the desired subset.  The pUserData field
       * of the FIELDINFO structure is utilized for this. */
      while (pFieldInfo)
      {
        if (SHORT1FROMMP(mp1) == CNR_FILTER_GASPOWERED)
        {
          /* If the desired subset is Gas-Powered then make the
           * columns labeled with a "2" invisible.
           * "2" -> Manual Powered column only. */
          if (pFieldInfo->pUserData == (PVOID)2))
            pFieldInfo->flData |= CFA_INVISIBLE;
          else
            pFieldInfo->flData &= ~CFA_INVISIBLE;
        }
        else
        {
          /* If the desired subset is Manual then make the
           * columns labeled with a "1" invisible.
           * "1" -> Gas Powered column only. */
          if (pFieldInfo->pUserData == (PVOID)1))
            pFieldInfo->flData |= CFA_INVISIBLE;
          else
            pFieldInfo->flData &= ~CFA_INVISIBLE;
        }
        pFieldInfo = (PFIELDINFO)WinSendMsg (hwndCnr,
                                             CM_QUERYDETAILFIELDINFO,
                                             MPFROMP(pFieldInfo),
                                             MPFROMSHORT(CMA_NEXT));
      }

      /* Refresh the Details View completely. */
      WinSendMsg (hwndCnr, CM_INVALIDATEDETAILFIELDINFO, NULL, NULL);
    }
    break;
