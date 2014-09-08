/* This function will change a specified record's position and-or
 * attributes for a particular container. */
BOOL ChangeRecordPosAndAttr(HWND hwndCnrChange, PMINIRECORDCORE pRecord,
                            LONG DeltaX, LONG DeltaY, LONG NewAttrs)
{
 USHORT  usFlag = 0;

 /* Query the current information for the pRecord that is contained in
  * hwndCnrChange. */
 if (WinSendMsg (hwndCnrChange, CM_QUERYRECORDINFO,
                 MPFROMP(&pRecord), MPFROMSHORT(1)))
 {
   /* Check to see if the new attributes are indeed different than the
    * current record attributes.  If they are different, set the
    * attributes and the minimum invalidate flag necessary. */
   if (pRecord->flRecordAttr != NewAttrs)
   {
     pRecord->flRecordAttr = NewAttrs;
     usFlag = CMA_NOREPOSITION;
   }

   /* Make sure at least one of the delta amounts is not 0.  If so,
    * change the current (x,y) by the delta amount and reset the
    * invalidate flag such that the record will go to its new position. */
   if (DeltaX || DeltaY)
   {
     pRecord->ptlIcon.x += DeltaX;
     pRecord->ptlIcon.y += DeltaY;
     usFlag = CMA_REPOSITION;
   }

   /* If usFlag is set, a change has taken place with the record.
    * Erase the record and invalidate it at its new position. */
   if (usFlag)
   {
     WinSendMsg (hwndCnrChange, CM_ERASERECORD, MPFROMP(pRecord), NULL);
     return ((BOOL)WinSendMsg (hwndCnrChange, CM_INVALIDATERECORD,
                               MPFROMP(&pRecord), MPFROM2SHORT(1, usFlag)));
   }
   else
   /* No error existed, but the record did not change either. */
     return (TRUE);
 }

 /* CM_QUERYRECORDINFO returned FALSE indicating that the given record
  * does not exist in the container specified by hwndCnrChange. */
 return (FALSE);
}
